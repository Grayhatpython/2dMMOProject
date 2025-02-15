// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Enum.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3017000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3017001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Enum_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Enum_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Enum_2eproto;
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

enum CreatureState : int {
  CREATURE_STATE_IDLE = 0,
  CREATURE_STATE_MOVING = 1,
  CREATURE_STATE_SKILL = 2,
  CREATURE_STATE_DEAD = 3,
  CreatureState_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  CreatureState_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool CreatureState_IsValid(int value);
constexpr CreatureState CreatureState_MIN = CREATURE_STATE_IDLE;
constexpr CreatureState CreatureState_MAX = CREATURE_STATE_DEAD;
constexpr int CreatureState_ARRAYSIZE = CreatureState_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* CreatureState_descriptor();
template<typename T>
inline const std::string& CreatureState_Name(T enum_t_value) {
  static_assert(::std::is_same<T, CreatureState>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function CreatureState_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    CreatureState_descriptor(), enum_t_value);
}
inline bool CreatureState_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, CreatureState* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<CreatureState>(
    CreatureState_descriptor(), name, value);
}
enum MoveDir : int {
  MOVE_DIR_NONE = 0,
  MOVE_DIR_UP = 1,
  MOVE_DIR_DOWN = 2,
  MOVE_DIR_LEFT = 3,
  MOVE_DIR_RIGHT = 4,
  MOVE_DIR_UP_LEFT = 5,
  MOVE_DIR_UP_RIGHT = 6,
  MOVE_DIR_DOWN_LEFT = 7,
  MOVE_DIR_DOWN_RIGHT = 8,
  MoveDir_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  MoveDir_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool MoveDir_IsValid(int value);
constexpr MoveDir MoveDir_MIN = MOVE_DIR_NONE;
constexpr MoveDir MoveDir_MAX = MOVE_DIR_DOWN_RIGHT;
constexpr int MoveDir_ARRAYSIZE = MoveDir_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MoveDir_descriptor();
template<typename T>
inline const std::string& MoveDir_Name(T enum_t_value) {
  static_assert(::std::is_same<T, MoveDir>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function MoveDir_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    MoveDir_descriptor(), enum_t_value);
}
inline bool MoveDir_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, MoveDir* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<MoveDir>(
    MoveDir_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::Protocol::CreatureState> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::CreatureState>() {
  return ::Protocol::CreatureState_descriptor();
}
template <> struct is_proto_enum< ::Protocol::MoveDir> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::MoveDir>() {
  return ::Protocol::MoveDir_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto
