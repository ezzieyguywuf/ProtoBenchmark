#include <iostream>

#include "MyProto.pb.h"
#include "absl/status/statusor.h"
#include "benchmark/benchmark.h"

void ModifyInput(MyProto* my_proto) {
  my_proto->set_timestamp(1112131415);
  my_proto->mutable_attributes()->set_resource("something else");
  my_proto->mutable_attributes()->clear_maybe_blank();
  my_proto->mutable_attributes()->clear_also_maybe_blank();
}

absl::StatusOr<MyProto> TransformInput(MyProto my_proto) {
  my_proto.set_timestamp(1112131415);
  my_proto.mutable_attributes()->set_resource("something else");
  my_proto.mutable_attributes()->clear_maybe_blank();
  my_proto.mutable_attributes()->clear_also_maybe_blank();

  return my_proto;
}

MyProto make_proto() {
  MyProto my_proto;
  my_proto.set_uid(12345);
  my_proto.set_timestamp(678910);
  (*my_proto.mutable_metadata())["key"] = "value";
  Attributes attributes;
  attributes.set_type(TYPEI);
  attributes.set_resource("resource");
  attributes.set_maybe_blank("not blank");
  attributes.set_also_maybe_blank("also not blank");
  *my_proto.mutable_attributes() = attributes;

  return my_proto;
}

void BM_Modify(benchmark::State& state) {
  MyProto my_proto = make_proto();

  for (auto s : state) {
    ModifyInput(&my_proto);
  }
}

void BM_Transform(benchmark::State& state) {
  MyProto my_proto = make_proto();

  for (auto s : state) {
    if (absl::StatusOr<MyProto> status = TransformInput(my_proto);
        status.ok()) {
      my_proto = *status;
    } else {
      std::cout << "error: " << status.status();
    }
  }
}

BENCHMARK(BM_Modify);
BENCHMARK(BM_Transform);

int main() { benchmark::RunSpecifiedBenchmarks(); }
