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

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using greet::AnalogyGRPCLogMessage;
using greet::AnalogyMessageReply;
using greet::Analogy;


namespace Kama
{
   

    class GreeterClient {
    public:
        GreeterClient(const GreeterClient&) = delete;

        GreeterClient(GreeterClient&&) = delete;

        GreeterClient& operator=(const GreeterClient&) = delete;

        GreeterClient& operator=(GreeterClient&&) = delete;

        static GreeterClient& getInstance() {
            static GreeterClient kSingleInstance;
            return kSingleInstance;
        }
        bool init(const std::string& name, const std::string& server);

        void runGreeter();

        void stopGreeter();

    private:
        GreeterClient() = default;

        virtual ~GreeterClient() = default;
    private:

        std::atomic_bool running_{ false };

        std::unique_ptr<Analogy::Stub> stub_;
        ::grpc::ClientContext context_{};
        std::unique_ptr<::grpc::ClientWriter<greet::AnalogyGRPCLogMessage>>     publish_stream{};
        greet::AnalogyGRPCLogMessage msg;
    };

}