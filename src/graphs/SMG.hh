#pragma once

#include <set>
#include <map>
#include <memory>
#include "graphs/SMGEdgeHasValue.hh"
#include "graphs/SMGEdgePointsTo.hh"
#include "graphs/SMGValue.hh"
#include "objects/SMGObject.hh"

namespace smg {

template <class T> class SMGEntitySet {
 private:
  std::set<std::shared_ptr<T>> entity_set;

 public:
  typename std::set<std::shared_ptr<T>>::size_type size() const noexcept;
  bool contains(std::shared_ptr<T> element) const;
  bool empty() const noexcept;

  void add(const std::shared_ptr<T> element);
};

class SMG {
 private:
  SMGEntitySet<const SMGObject> objects_;
  std::set<SMGValue> values_;
  std::map<SMGValue, SMGEdgePointsToPtr> pt_edges_;
  SMGEntitySet<const SMGEdgeHasValue> hv_edges_;

  SMGObjectPtr null_object_ = SMGNullObject::GetNullObject();
  SMGValue null_value_ = SMGValue::GetNullValue();

 public:
  SMG();
  virtual ~SMG();

  void AddObject(const SMGObjectPtr& object);
  void AddValue(const SMGValue& value);
  void AddPointsToEdge(const SMGEdgePointsToPtr& edge);
  void AddHasValueEdge(const SMGEdgeHasValuePtr& edge);

  SMGObjectPtr GetNullObject() const;
  const SMGValue GetNullValue() const;

  const SMGEntitySet<const SMGObject>& GetObjects() const;
  const std::set<SMGValue>& GetValues() const;
  const std::map<SMGValue, SMGEdgePointsToPtr>& GetPTEdges() const;
  const SMGEntitySet<const SMGEdgeHasValue>& GetHVEdges() const;

  const SMGObjectPtr GetObjectPointedBy(const SMGValue& value) const;
};

template <class T> inline void SMGEntitySet<T>::add(std::shared_ptr<T> element) {
  entity_set.insert(element);
}

template <class T>
inline typename std::set<std::shared_ptr<T>>::size_type SMGEntitySet<T>::size() const noexcept {
  return entity_set.size();
}

template <class T> inline bool SMGEntitySet<T>::contains(std::shared_ptr<T> element) const {
  return entity_set.count(element);
}

template <class T> inline bool SMGEntitySet<T>::empty() const noexcept {
  return entity_set.empty();
}

}  // namespace smg