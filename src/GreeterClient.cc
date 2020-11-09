/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "../proto/Analogy.grpc.pb.h"
#include "GreeterClient.h"
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <thread>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using greet::AnalogyGRPCLogMessage;
using greet::AnalogyMessageReply;
using greet::Analogy;
using namespace Kama;



bool GreeterClient::init(const std::string& name, const std::string& server) {
    stub_ = ::Analogy::NewStub(grpc::CreateChannel(server, grpc::InsecureChannelCredentials()));
    return true;
}

void GreeterClient::runGreeter() {
    running_ = true;
    greet::AnalogyMessageReply reply;
    publish_stream = stub_->SubscribeForPublishingMessages(&context_, &reply);

    std::thread thread_for_request{ [this] {
        uint64_t increase_name{0};
        uint64_t counter = 0;
       
        greet::AnalogyGRPCLogMessage msg;
        while (running_) {
           
            msg.set_text("test"+std::to_string(counter));
            counter++;
            if (!publish_stream->Write(msg)) {          
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    } };
    if (thread_for_request.joinable()) { thread_for_request.join(); }
}

void GreeterClient::stopGreeter() {
    if (!running_) { return; }
    running_ = false;
    context_.TryCancel();
}
