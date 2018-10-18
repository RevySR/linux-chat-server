#include "chatserver.hpp"

ChatServer::ChatServer(io_service& service, unsigned short port)
    :service{service}, acceptor{this->service, tcp::endpoint{tcp::v4(), port}} {

}

void ChatServer::start() {
    auto chatConnectionPtr = std::make_shared<ChatConnection>(service);
    acceptor.async_accept(chatConnectionPtr->getSocket(),
                          [chatConnectionPtr, this]
                          (BOOST_ASIO_UNUSED_VARIABLE error_code const& errorCode) {
        if(errorCode) {
//            cout<<"accept err:"<<err.message()<<"\n";
            return;
        }
//        chatConnectionPtr->start();
        this->start();
    });
}