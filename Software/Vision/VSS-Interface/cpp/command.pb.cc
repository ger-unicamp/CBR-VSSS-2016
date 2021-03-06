// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: command.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "command.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace vss_command {

namespace {

const ::google::protobuf::Descriptor* Robot_Command_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Robot_Command_reflection_ = NULL;
const ::google::protobuf::Descriptor* Global_Commands_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Global_Commands_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_command_2eproto() {
  protobuf_AddDesc_command_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "command.proto");
  GOOGLE_CHECK(file != NULL);
  Robot_Command_descriptor_ = file->message_type(0);
  static const int Robot_Command_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Robot_Command, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Robot_Command, left_vel_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Robot_Command, right_vel_),
  };
  Robot_Command_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Robot_Command_descriptor_,
      Robot_Command::default_instance_,
      Robot_Command_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Robot_Command, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Robot_Command, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Robot_Command));
  Global_Commands_descriptor_ = file->message_type(1);
  static const int Global_Commands_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Global_Commands, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Global_Commands, is_team_yellow_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Global_Commands, robot_commands_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Global_Commands, situation_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Global_Commands, name_),
  };
  Global_Commands_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Global_Commands_descriptor_,
      Global_Commands::default_instance_,
      Global_Commands_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Global_Commands, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Global_Commands, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Global_Commands));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_command_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Robot_Command_descriptor_, &Robot_Command::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Global_Commands_descriptor_, &Global_Commands::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_command_2eproto() {
  delete Robot_Command::default_instance_;
  delete Robot_Command_reflection_;
  delete Global_Commands::default_instance_;
  delete Global_Commands_reflection_;
}

void protobuf_AddDesc_command_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rcommand.proto\022\013vss_command\"@\n\rRobot_Co"
    "mmand\022\n\n\002id\030\001 \002(\r\022\020\n\010left_vel\030\002 \002(\002\022\021\n\tr"
    "ight_vel\030\003 \002(\002\"\212\001\n\017Global_Commands\022\n\n\002id"
    "\030\001 \001(\r\022\026\n\016is_team_yellow\030\002 \001(\010\0222\n\016robot_"
    "commands\030\003 \003(\0132\032.vss_command.Robot_Comma"
    "nd\022\021\n\tsituation\030\004 \001(\r\022\014\n\004name\030\005 \001(\t", 235);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "command.proto", &protobuf_RegisterTypes);
  Robot_Command::default_instance_ = new Robot_Command();
  Global_Commands::default_instance_ = new Global_Commands();
  Robot_Command::default_instance_->InitAsDefaultInstance();
  Global_Commands::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_command_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_command_2eproto {
  StaticDescriptorInitializer_command_2eproto() {
    protobuf_AddDesc_command_2eproto();
  }
} static_descriptor_initializer_command_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Robot_Command::kIdFieldNumber;
const int Robot_Command::kLeftVelFieldNumber;
const int Robot_Command::kRightVelFieldNumber;
#endif  // !_MSC_VER

Robot_Command::Robot_Command()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:vss_command.Robot_Command)
}

void Robot_Command::InitAsDefaultInstance() {
}

Robot_Command::Robot_Command(const Robot_Command& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:vss_command.Robot_Command)
}

void Robot_Command::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  left_vel_ = 0;
  right_vel_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Robot_Command::~Robot_Command() {
  // @@protoc_insertion_point(destructor:vss_command.Robot_Command)
  SharedDtor();
}

void Robot_Command::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Robot_Command::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Robot_Command::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Robot_Command_descriptor_;
}

const Robot_Command& Robot_Command::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_command_2eproto();
  return *default_instance_;
}

Robot_Command* Robot_Command::default_instance_ = NULL;

Robot_Command* Robot_Command::New() const {
  return new Robot_Command;
}

void Robot_Command::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Robot_Command*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(id_, right_vel_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Robot_Command::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:vss_command.Robot_Command)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 id = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(21)) goto parse_left_vel;
        break;
      }

      // required float left_vel = 2;
      case 2: {
        if (tag == 21) {
         parse_left_vel:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &left_vel_)));
          set_has_left_vel();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(29)) goto parse_right_vel;
        break;
      }

      // required float right_vel = 3;
      case 3: {
        if (tag == 29) {
         parse_right_vel:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &right_vel_)));
          set_has_right_vel();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:vss_command.Robot_Command)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:vss_command.Robot_Command)
  return false;
#undef DO_
}

void Robot_Command::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:vss_command.Robot_Command)
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  // required float left_vel = 2;
  if (has_left_vel()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(2, this->left_vel(), output);
  }

  // required float right_vel = 3;
  if (has_right_vel()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(3, this->right_vel(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:vss_command.Robot_Command)
}

::google::protobuf::uint8* Robot_Command::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:vss_command.Robot_Command)
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  // required float left_vel = 2;
  if (has_left_vel()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(2, this->left_vel(), target);
  }

  // required float right_vel = 3;
  if (has_right_vel()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(3, this->right_vel(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:vss_command.Robot_Command)
  return target;
}

int Robot_Command::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // required float left_vel = 2;
    if (has_left_vel()) {
      total_size += 1 + 4;
    }

    // required float right_vel = 3;
    if (has_right_vel()) {
      total_size += 1 + 4;
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Robot_Command::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Robot_Command* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Robot_Command*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Robot_Command::MergeFrom(const Robot_Command& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_left_vel()) {
      set_left_vel(from.left_vel());
    }
    if (from.has_right_vel()) {
      set_right_vel(from.right_vel());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Robot_Command::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Robot_Command::CopyFrom(const Robot_Command& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Robot_Command::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void Robot_Command::Swap(Robot_Command* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(left_vel_, other->left_vel_);
    std::swap(right_vel_, other->right_vel_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Robot_Command::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Robot_Command_descriptor_;
  metadata.reflection = Robot_Command_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Global_Commands::kIdFieldNumber;
const int Global_Commands::kIsTeamYellowFieldNumber;
const int Global_Commands::kRobotCommandsFieldNumber;
const int Global_Commands::kSituationFieldNumber;
const int Global_Commands::kNameFieldNumber;
#endif  // !_MSC_VER

Global_Commands::Global_Commands()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:vss_command.Global_Commands)
}

void Global_Commands::InitAsDefaultInstance() {
}

Global_Commands::Global_Commands(const Global_Commands& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:vss_command.Global_Commands)
}

void Global_Commands::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  id_ = 0u;
  is_team_yellow_ = false;
  situation_ = 0u;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Global_Commands::~Global_Commands() {
  // @@protoc_insertion_point(destructor:vss_command.Global_Commands)
  SharedDtor();
}

void Global_Commands::SharedDtor() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (this != default_instance_) {
  }
}

void Global_Commands::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Global_Commands::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Global_Commands_descriptor_;
}

const Global_Commands& Global_Commands::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_command_2eproto();
  return *default_instance_;
}

Global_Commands* Global_Commands::default_instance_ = NULL;

Global_Commands* Global_Commands::New() const {
  return new Global_Commands;
}

void Global_Commands::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Global_Commands*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 27) {
    ZR_(id_, is_team_yellow_);
    situation_ = 0u;
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        name_->clear();
      }
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  robot_commands_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Global_Commands::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:vss_command.Global_Commands)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 id = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_is_team_yellow;
        break;
      }

      // optional bool is_team_yellow = 2;
      case 2: {
        if (tag == 16) {
         parse_is_team_yellow:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &is_team_yellow_)));
          set_has_is_team_yellow();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_robot_commands;
        break;
      }

      // repeated .vss_command.Robot_Command robot_commands = 3;
      case 3: {
        if (tag == 26) {
         parse_robot_commands:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_robot_commands()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_robot_commands;
        if (input->ExpectTag(32)) goto parse_situation;
        break;
      }

      // optional uint32 situation = 4;
      case 4: {
        if (tag == 32) {
         parse_situation:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &situation_)));
          set_has_situation();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(42)) goto parse_name;
        break;
      }

      // optional string name = 5;
      case 5: {
        if (tag == 42) {
         parse_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "name");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:vss_command.Global_Commands)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:vss_command.Global_Commands)
  return false;
#undef DO_
}

void Global_Commands::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:vss_command.Global_Commands)
  // optional uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  // optional bool is_team_yellow = 2;
  if (has_is_team_yellow()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->is_team_yellow(), output);
  }

  // repeated .vss_command.Robot_Command robot_commands = 3;
  for (int i = 0; i < this->robot_commands_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->robot_commands(i), output);
  }

  // optional uint32 situation = 4;
  if (has_situation()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->situation(), output);
  }

  // optional string name = 5;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      5, this->name(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:vss_command.Global_Commands)
}

::google::protobuf::uint8* Global_Commands::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:vss_command.Global_Commands)
  // optional uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  // optional bool is_team_yellow = 2;
  if (has_is_team_yellow()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->is_team_yellow(), target);
  }

  // repeated .vss_command.Robot_Command robot_commands = 3;
  for (int i = 0; i < this->robot_commands_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->robot_commands(i), target);
  }

  // optional uint32 situation = 4;
  if (has_situation()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->situation(), target);
  }

  // optional string name = 5;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->name(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:vss_command.Global_Commands)
  return target;
}

int Global_Commands::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // optional bool is_team_yellow = 2;
    if (has_is_team_yellow()) {
      total_size += 1 + 1;
    }

    // optional uint32 situation = 4;
    if (has_situation()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->situation());
    }

    // optional string name = 5;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

  }
  // repeated .vss_command.Robot_Command robot_commands = 3;
  total_size += 1 * this->robot_commands_size();
  for (int i = 0; i < this->robot_commands_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->robot_commands(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Global_Commands::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Global_Commands* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Global_Commands*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Global_Commands::MergeFrom(const Global_Commands& from) {
  GOOGLE_CHECK_NE(&from, this);
  robot_commands_.MergeFrom(from.robot_commands_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_is_team_yellow()) {
      set_is_team_yellow(from.is_team_yellow());
    }
    if (from.has_situation()) {
      set_situation(from.situation());
    }
    if (from.has_name()) {
      set_name(from.name());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Global_Commands::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Global_Commands::CopyFrom(const Global_Commands& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Global_Commands::IsInitialized() const {

  if (!::google::protobuf::internal::AllAreInitialized(this->robot_commands())) return false;
  return true;
}

void Global_Commands::Swap(Global_Commands* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(is_team_yellow_, other->is_team_yellow_);
    robot_commands_.Swap(&other->robot_commands_);
    std::swap(situation_, other->situation_);
    std::swap(name_, other->name_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Global_Commands::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Global_Commands_descriptor_;
  metadata.reflection = Global_Commands_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace vss_command

// @@protoc_insertion_point(global_scope)
