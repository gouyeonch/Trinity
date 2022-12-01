#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include "json.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string toknizName(string str)
{
    int npos = str.find(' ');

    if(npos != -1) str.erase(npos);

    return str.substr(0, str.length()-1);
}

//00:00:00을 초로 환산
int timePars(string time)
{
    int t = stoi(time.substr(0, 2)) * 3600;
    t += stoi(time.substr(3, 2)) * 60;
    t += stoi(time.substr(6, 2));

    return t;
}

//문자열로 전해진 시간 두 시간의 차이를 구해줌
int difftime(string t1 = "00:00:00" , string t2 = "00:00:00")
{
    //cout << t1 <<" "<<t2<<endl;
    return timePars(t2) - timePars(t1);
}

//지하철역 정보(역코드) 검색 api
//역의 이름과 호선을 입력하면 해당 역의 코드를 반환
string requestCode(string name, string line)
{
    //input
        // KEY	String(필수)	인증키	OpenAPI 에서 발급된 인증키
        // TYPE	String(필수)	요청파일타입	xml : xml, xml파일 : xmlf, 엑셀파일 : xls, json파일 : json
        // SERVICE	String(필수)	서비스명	SearchInfoBySubwayNameService
        // START_INDEX	INTEGER(필수)	요청시작위치	정수 입력 (페이징 시작번호 입니다 : 데이터 행 시작번호)
        // END_INDEX	INTEGER(필수)	요청종료위치	정수 입력 (페이징 끝번호 입니다 : 데이터 행 끝번호)
        // STATION_NM	STRING(선택)	전철역명	전철역명 문자값
    //ouput
        // 1	STATION_CD	전철역코드
        // 2	STATION_NM	전철역명
        // 4	LINE_NUM	호선
        // 5	FR_CODE	외부코드
    string code;
    boost::asio::io_context ioc;
    boost::asio::ip::tcp::resolver resolver(ioc);
    boost::beast::tcp_stream stream(ioc);

    try {
        auto const host = "openAPI.seoul.go.kr";
        auto const port = "8088";
        auto const target = "/5177664a6a676f7536334e5a685047/json/SearchInfoBySubwayNameService/1/6/" + name + "/";
        bool isVer1_0 = false;
        int version = isVer1_0 ? 10 : 11;

        auto const results = resolver.resolve(host, port);
        stream.connect(results);

        string urlHost = host;
        urlHost += ":";
        urlHost += port;

        boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::get, target, version};
        req.set(boost::beast::http::field::host, urlHost);
        req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        boost::beast::http::write(stream, req);

        boost::beast::flat_buffer buffer;

        boost::beast::http::response<boost::beast::http::dynamic_body> res;

        boost::beast::http::read(stream, buffer, res);

        string json = boost::beast::buffers_to_string(res.body().data());

        Json::Reader reader;
        Json::Value root;
        reader.parse(json, root);

        const Json::Value &name = root["SearchInfoBySubwayNameService"]["row"];
        for(int i = 0; i < name.size(); i++)
        {
            if(name[i]["LINE_NUM"].asString() == line) code = name[i]["STATION_CD"].asString();
        }

        boost::beast::error_code ec;
        stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

        if (ec && ec != boost::beast::errc::not_connected) {
            clog << "error: " << ec.message() << endl;
        }

        return code;
    } catch (std::exception const& ex) {
        clog << "exception: " << ex.what() << endl;

    }
}

//지하철역 정보 검색 api
Json::Value requestStat(string code, string &T, string D = "1")
{
    //input
        // KEY	        String(필수)	인증키	OpenAPI 에서 발급된 인증키
        // TYPE	        String(필수)	요청파일타입	xml : xml, xml파일 : xmlf, 엑셀파일 : xls, json파일 : json
        // SERVICE	    String(필수)	서비스명	SearchSTNTimeTableByIDService
        // START_INDEX	INTEGER(필수)	요청시작위치	정수 입력 (페이징 시작번호 입니다 : 데이터 행 시작번호)
        // END_INDEX	INTEGER(필수)	요청종료위치	정수 입력 (페이징 끝번호 입니다 : 데이터 행 끝번호)
        // STATION_CD	STRING(필수)	전철역코드	전철역코드 문자값
        // WEEK_TAG	    STRING(필수)	요일	(1,2,3)
        // INOUT_TAG	STRING(필수)	상/하행선	

    //output
        // 1	LINE_NUM	호선
        // 2	FR_CODE	외부코드
        // 3	STATION_CD	전철역코드
        // 4	STATION_NM	전철역명
        // 5	TRAIN_NO	열차번호
        // 6	ARRIVETIME	도착시간
        // 7	LEFTTIME	출발시간
        // 8	ORIGINSTATION	출발지하철역코드
        // 9	DESTSTATION	도착지하철역코드
        // 10	SUBWAYSNAME	출발지하철역명
        // 11	SUBWAYENAME	도착지하철역명
        // 12	WEEK_TAG	요일
        // 13	INOUT_TAG	상/하행선
        // 14	FL_FLAG	플러그
        // 15	DESTSTATION2	도착역 코드2
        // 16	EXPRESS_YN	급행선
        // (G:일반(general) D: 급행(direct))
        // 17	BRANCH_LINE	지선
    boost::asio::io_context ioc;
    boost::asio::ip::tcp::resolver resolver(ioc);
    boost::beast::tcp_stream stream(ioc);
    try {
        auto const host = "openAPI.seoul.go.kr";
        auto const port = "8088";
        auto const target = "/5a69676576676f753130396773557045/json/SearchSTNTimeTableByIDService/1/150/" + code + "/1/" + D + "/";

        bool isVer1_0 = false;
        int version = isVer1_0 ? 10 : 11;

        auto const results = resolver.resolve(host, port);
        stream.connect(results);

        string urlHost = host;
        urlHost += ":";
        urlHost += port;

        boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::get, target, version};
        req.set(boost::beast::http::field::host, urlHost);
        req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        boost::beast::http::write(stream, req);

        boost::beast::flat_buffer buffer;

        boost::beast::http::response<boost::beast::http::dynamic_body> res;

        boost::beast::http::read(stream, buffer, res);

        string json = boost::beast::buffers_to_string(res.body().data());

        Json::Reader reader;
        Json::Value root;
        reader.parse(json, root);

        const Json::Value &time = root["SearchSTNTimeTableByIDService"]["row"][0]["LEFTTIME"];
        T = time.asString();

        boost::beast::error_code ec;
        stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

        if (ec && ec != boost::beast::errc::not_connected) {
            clog << "error: " << ec.message() << endl;
            //return -1;
        }

        return root;
    } catch (std::exception const& ex) {
        clog << "exception: " << ex.what() << endl;

        //return -1;
    }

}

int reFacStat(Json::Value s1, Json::Value s2)
{
    string stak1, stak2, start1, start2, end1, end2, name1, name2, flag = "LEFTTIME";
    int diffTime, size1, size2, min=9999;

    name1 = s1["SearchSTNTimeTableByIDService"]["row"][0]["STATION_NM"].asString();
    name2 = s2["SearchSTNTimeTableByIDService"]["row"][0]["STATION_NM"].asString();
    size1 = s1["SearchSTNTimeTableByIDService"]["row"].size();
    size2 = s2["SearchSTNTimeTableByIDService"]["row"].size();

    for(int i = 0; i < size1; i++)
    {
        start1 = s1["SearchSTNTimeTableByIDService"]["row"][i]["SUBWAYSNAME"].asString();
        end1 = s1["SearchSTNTimeTableByIDService"]["row"][i]["SUBWAYENAME"].asString();

        if(start1 == name1) flag = "LEFTTIME";
        if(end1 == name1) flag = "ARRIVETIME";

        stak1 = s1["SearchSTNTimeTableByIDService"]["row"][i][flag].asString();

        for(int j = 0; j < size2; j++)
        {
            start2 = s1["SearchSTNTimeTableByIDService"]["row"][j]["SUBWAYSNAME"].asString();
            end2 = s1["SearchSTNTimeTableByIDService"]["row"][j]["SUBWAYENAME"].asString();

            if(start2 == name2) flag = "LEFTTIME";
            if(end2 == name2) flag = "ARRIVETIME";

            stak2 = s2["SearchSTNTimeTableByIDService"]["row"][j][flag].asString();
            
            if(start1 == start2 && end1 == end2)
            {
                diffTime = difftime(stak1, stak2);
                //cout << "       " << stak1 << " "<<stak2<<endl;
                if(diffTime > 60 && min > diffTime) 
                {
                    min = diffTime;
                    //cout << "       " << stak1 << " "<<stak2<<endl;
                    //cout << "       " << min << endl;
                }
                
            }

        }
    }

    return min;
}

int main(int argc, char* argv[]) 
{
    string name, nameNxt, time, timeNxt, line, str, code, flag;
    ifstream readName;
    ofstream writeInf;
    int npos, diffTime;
    Json::Value json_1, jsonNxt_1, json_2, jsonNxt_2;

    readName.open("StatName.txt");
    writeInf.open("StatData.txt", ios_base::out);

    if(readName.is_open() && writeInf.is_open())
    {
        //호선 받아오기
        getline(readName, str);
        line = toknizName(str);

        while(!readName.eof())
        {
            //종착역으로 변수 초기화
            getline(readName, str);
            name = toknizName(str);
            code = requestCode(name, line);
            json_1 = requestStat(code, time);

            getline(readName, str);

            while(flag != "0" && !readName.eof())
            {
                nameNxt = toknizName(str);
                code = requestCode(nameNxt, line);
                jsonNxt_1 = requestStat(code, timeNxt);
                
                diffTime = difftime(time, timeNxt);

                if(diffTime < 0 || 150 < diffTime) diffTime = reFacStat(json_1, jsonNxt_1);
                
                writeInf << line[1] << " " << name << " " << diffTime << " " << nameNxt << "\n";

                // cout << name << endl;
                // cout << nameNxt << endl;
                // cout << time << endl;
                // cout << timeNxt << endl;
                // cout<<diffTime<<endl;

                name = nameNxt;
                time = timeNxt;
                json_1 = jsonNxt_1;

                getline(readName, str);
                flag = str.substr(0, 1);
            }
            line = toknizName(str);
            //cout << line << endl;
            flag = "1";
        }
    }

    readName.close();
    writeInf.close();

    return 0;
}