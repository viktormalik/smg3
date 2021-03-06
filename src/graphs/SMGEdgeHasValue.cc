#include "SMGEdgeHasValue.hh"
#include <iostream>
#include "exceptions/IllegalArgumentException.hh"

namespace smg {

SMGEdgeHasValue::SMGEdgeHasValue(const SMGCType& type,
                                 const int offset,
                                 const SMGObject& object,
                                 const SMGValue& value)
    : SMGEdge(value, object), offset_(offset), type_(type) {}

long SMGEdgeHasValue::GetOffset() const { return offset_; }

const SMGCType& SMGEdgeHasValue::GetType() const { return type_; }

int SMGEdgeHasValue::GetSizeInBytes() const { return type_.GetSize(); }

bool SMGEdgeHasValue::IsConsistentWith(const SMGEdgeHasValue& other) const {
  if (GetObject().GetId() == other.GetObject().GetId() && offset_ == other.offset_ &&
      (&(type_) == &(other.type_))) {
    return GetValue().GetId() == other.GetValue().GetId();
  }

  return true;
}

bool SMGEdgeHasValue::OverlapsWith(const SMGEdgeHasValue& other) const {
  if (GetObject().GetId() != other.GetObject().GetId()) {
    std::string message =
        "Call of overlapsWith() on Has-Value edges pair not originating from the same object";
    throw IllegalArgumentException(message.c_str());
  }

  const int otStart = other.GetOffset();
  const int otEnd = otStart + other.GetSizeInBytes();

  return OverlapsWith(otStart, otEnd);
}

bool SMGEdgeHasValue::OverlapsWith(const int other_start, const int other_end) const {
  int myStart = offset_;
  int myEnd = myStart + type_.GetSize();

  if (myStart < other_start) {
    return (myEnd > other_start);
  } else if (other_start < myStart) {
    return (other_end > myStart);
  }

  // Start offsets are equal, always overlap
  return true;
}

bool SMGEdgeHasValue::IsCompatibleField(const SMGEdgeHasValue& other) const {
  return &type_ == &(other.type_) && (offset_ == other.offset_);
}

bool SMGEdgeHasValue::IsCompatibleFieldOnSameObject(const SMGEdgeHasValue& other) const {
  return IsCompatibleField(other) && (GetObject().GetId() == other.GetObject().GetId());
}

}  // namespace smg
