// This runs the examples with the tests
#include <boost/test/unit_test.hpp>

#include <boost/asio.hpp>
using namespace boost;
using namespace boost::asio::ip;

const int MAX_LENGTH = 1024;

BOOST_AUTO_TEST_CASE(ASIO) {
   // Both server and client
   asio::io_service io_service;
   
   // Server, start listening on an open port
   tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 0));

   // Client, connect to server
   tcp::socket client(io_service);
   client.connect(tcp::endpoint(address_v4().from_string("127.0.0.1"), acceptor.local_endpoint().port()));

   // Server, accept connection from client
   tcp::socket firstOpened(io_service);
   acceptor.accept(firstOpened);

   // Client, send some data
   std::string clientData = "Data From Client";
   client.send(asio::buffer(clientData.c_str(), clientData.length() + 1));

   // Server, read data from client
   char dataReceived[MAX_LENGTH];
   firstOpened.read_some(asio::buffer(dataReceived));
   std::string acceptedData = dataReceived;
   // acceptedData == "Data from Client"
   
   // Server, send response back to client
   std::string sendData = "Data back from server";
   firstOpened.send(asio::buffer(sendData.c_str(), sendData.length() + 1));

   // Client, read data from server
   memset(dataReceived, 0, MAX_LENGTH);
   client.read_some(asio::buffer(dataReceived));
   std::string backFromServer = dataReceived;
   // backFromServer == "Data back from server"
}