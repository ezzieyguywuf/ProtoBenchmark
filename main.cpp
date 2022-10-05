#include <iostream>

#include "MyProto.pb.h"
#include "absl/log/check.h"
#include "absl/status/statusor.h"
#include "benchmark/benchmark.h"
MyProto make_proto() {
  MyProto my_proto;
  my_proto.set_uid(12345);
  my_proto.set_timestamp(678910);
  for (int i = 0; i < 1000; ++i) {
    (*my_proto.mutable_metadata())[std::to_string(i)] = "value";
  }
  Attributes attributes;
  attributes.set_type(TYPEI);
  attributes.set_resource("resource");
  attributes.set_maybe_blank("not blank");
  attributes.set_also_maybe_blank("also not blank");
  *my_proto.mutable_attributes() = attributes;

  return my_proto;
}

MyProto GetExisting() {
  MyProto my_proto;
  my_proto.set_uid(12345);
  my_proto.set_timestamp(678910);
  for (int i = 0; i < 100000; ++i) {
    (*my_proto.mutable_metadata())[std::to_string(i)] = "value";
  }
  Attributes attributes;
  attributes.set_type(TYPEI);
  attributes.set_resource("resource");
  attributes.set_maybe_blank("not blank");
  attributes.set_also_maybe_blank("also not blank");
  *my_proto.mutable_attributes() = attributes;

  return my_proto;
}

absl::Status ModifyInput(MyProto* my_proto) {
  MyProto local_proto = GetExisting();

  local_proto.set_timestamp(1112131415);
  local_proto.mutable_attributes()->set_resource("something else");
  local_proto.mutable_attributes()->clear_maybe_blank();
  local_proto.mutable_attributes()->clear_also_maybe_blank();
  local_proto.clear_metadata();

  *my_proto = std::move(local_proto);

  return absl::OkStatus();
}

absl::StatusOr<MyProto> TransformInput(const MyProto& my_proto) {
  MyProto local_proto = GetExisting();

  local_proto.set_timestamp(1112131415);
  local_proto.mutable_attributes()->set_resource("something else");
  local_proto.mutable_attributes()->clear_maybe_blank();
  local_proto.mutable_attributes()->clear_also_maybe_blank();
  local_proto.clear_metadata();

  return local_proto;
}

void BM_Modify(benchmark::State& state) {
  MyProto my_proto = make_proto();

  for (auto s : state) {
    CHECK_OK(ModifyInput(&my_proto));
  }
}

void BM_Transform(benchmark::State& state) {
  MyProto my_proto = make_proto();

  for (auto s : state) {
    absl::StatusOr<MyProto> status = TransformInput(my_proto);
    CHECK_OK(status);
  }
}

BENCHMARK(BM_Modify);
BENCHMARK(BM_Transform);

BENCHMARK_MAIN();
