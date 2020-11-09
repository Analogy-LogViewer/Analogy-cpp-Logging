cmake_minimum_required( VERSION 3.1 )

project( grpc_example )

find_package(gRPC CONFIG REQUIRED)

find_package( Protobuf REQUIRED )

add_executable( client src/main.cc src/GreeterClient.h src/GreeterClient.cc proto/Analogy.grpc.pb.cc proto/Analogy.pb.cc)

target_link_libraries( client PRIVATE gRPC::grpc++ gRPC::grpc++_reflection gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite )