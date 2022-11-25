#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include "json.h"
#include <iostream>

using namespace std;

int request(string code, string &N, string &T, string &L)
{
    boost::asio::io_context ioc;
    boost::asio::ip::tcp::resolver resolver(ioc);
    boost::beast::tcp_stream stream(ioc);
    try {
        auto const host = "openAPI.seoul.go.kr";
        auto const port = "8088";
        auto const target = "/5a69676576676f753130396773557045/json/SearchSTNTimeTableByIDService/1/1/" + code + "/1/1/";

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
        cout << json << endl;

        Json::Reader reader;
        Json::Value root;
        reader.parse(json, root);

        const Json::Value &name = root["SearchSTNTimeTableByIDService"]["row"][0]["STATION_NM"];
        N = name.asString();

        const Json::Value &time = root["SearchSTNTimeTableByIDService"]["row"][0]["ARRIVETIME"];
        T = time.asString();

        const Json::Value &line = root["SearchSTNTimeTableByIDService"]["row"][0]["LINE_NUM"];
        L = line.asString();

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

int main(int argc, char* argv[]) {
    string name, time, line;
    request("0150", name, time, line);

    cout << name << endl;
    cout << time << endl;
    cout << line << endl;

    return 0;
}