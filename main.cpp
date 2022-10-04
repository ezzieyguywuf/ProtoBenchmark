#include <iostream>

#include "MyProto.pb.h"
#include "absl/status/statusor.h"

void ModifyInput(MyProto* my_proto) {
  my_proto.set_timestamp(1112131415);
  my_proto.set_resource("something else");
  my_proto.clear_maybe_blank();
  my_proto.clear_also_maybe_blank();
}

absl::StatusOr<MyProto> TransformInput(MyProto my_proto) {
  my_proto.set_timestamp(1112131415);
  my_proto.set_resource("something else");
  my_proto.clear_maybe_blank();
  my_proto.clear_also_maybe_blank();

  return my_proto;
}

int main() {
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

  ModifyInput(&my_proto);
  my_proto = TransformInput(my_proto);

  std::cout << my_proto.DebugString();
}
