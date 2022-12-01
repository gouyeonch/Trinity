#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include "json.h"
#include <iostream>

using namespace std;

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

int requestStat(string code, string n = "1", string D = "1")
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
        auto const target = "/5a69676576676f753130396773557045/json/SearchSTNTimeTableByIDService/1/"+ n +"/" + code + "/1/" + D + "/";

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
        cout << json << endl;

<<<<<<< HEAD
        const Json::Value &time = root["SearchSTNTimeTableByIDService"]["row"][0]["ARRIVETIME"];
=======
        for(int i = 0; i <root["SearchSTNTimeTableByIDService"]["row"].size();i++)
        {
            cout << endl;
            cout << root["SearchSTNTimeTableByIDService"]["row"][i]["STATION_NM"]<< endl;
            cout << root["SearchSTNTimeTableByIDService"]["row"][i]["ARRIVETIME"]<< endl;
            cout << root["SearchSTNTimeTableByIDService"]["row"][i]["LEFTTIME"]<< endl;
            cout << root["SearchSTNTimeTableByIDService"]["row"][i]["SUBWAYSNAME"]<< endl;
            cout << root["SearchSTNTimeTableByIDService"]["row"][i]["SUBWAYENAME"]<< endl;
        }
>>>>>>> gouyeonch

        boost::beast::error_code ec;
        stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

        if (ec && ec != boost::beast::errc::not_connected) {
            clog << "error: " << ec.message() << endl;
            return -1;
        }
    } catch (std::exception const& ex) {
        clog << "exception: " << ex.what() << endl;

        return -1;
    }
}

int main()
{
<<<<<<< HEAD
    string s,n;
    int i;

    requestStat(requestCode("인천", "01호선"), "5");

=======
    string s,n,line;
    int i;

>>>>>>> gouyeonch
    cin >> i;

    if(i == 0)
    {
<<<<<<< HEAD
        cin >> s;
        requestStat(requestCode(s, "08호선"), "1");

        cin >> s;
        requestStat(requestCode(s, "08호선"), "1");
    }
    else{
        cin >> s >> n;
        requestStat(requestCode(s, "08호선"), n);
=======
        cin >> line;

        cin >> s;
        requestStat(requestCode(s, "0" + line + "호선"), "1");

        cin >> s;
        requestStat(requestCode(s, "0" + line + "호선"));
    }
    else{
        cin >> s >> n;
        cin >> line;
        requestStat(requestCode(s, "0" + line + "호선"), n);
>>>>>>> gouyeonch
    }

    return 0;
}
