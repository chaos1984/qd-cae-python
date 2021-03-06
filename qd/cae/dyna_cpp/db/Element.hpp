
#ifndef ELEMENT_HPP
#define ELEMENT_HPP

// includes
#include <dyna_cpp/utility/PythonUtility.hpp>

#include <cstdint>
#include <memory>
#include <set>
#include <vector>

namespace qd {

// forward declarations
class Node;
class DB_Elements;

class Element
{
public:
  enum ElementType
  {
    NONE,
    BEAM,
    SHELL,
    SOLID,
    TSHELL
  };

private:
  int32_t elementID;
  bool is_rigid;
  std::vector<size_t> nodes; // indexes
  std::vector<float> energy;
  std::vector<float> stress_mises;
  std::vector<float> plastic_strain;
  std::vector<std::vector<float>> strain;
  std::vector<std::vector<float>> stress;
  std::vector<std::vector<float>> history_vars;
  ElementType elemType;
  DB_Elements* db_elements;

public:
  explicit Element(const int32_t _id,
                   const ElementType _etype,
                   const std::vector<size_t>& _nodes,
                   DB_Elements* db_elements);
  bool operator<(const Element& other) const;
  inline std::string str()
  {
    return "<Element type:" + std::to_string(elemType) +
           " id:" + std::to_string(elementID) + ">";
  };
  void check() const;

  // getter
  ElementType get_elementType() const;
  int32_t get_elementID() const;
  bool get_is_rigid() const;
  float get_estimated_element_size() const; // fast
  std::vector<std::shared_ptr<Node>> get_nodes() const;
  std::vector<int32_t> get_node_ids() const;
  std::vector<size_t> get_node_indexes() const;
  std::vector<float> get_energy() const;
  std::vector<float> get_stress_mises() const;
  std::vector<float> get_plastic_strain() const;
  std::vector<std::vector<float>> get_coords() const;
  std::vector<std::vector<float>> get_strain() const;
  std::vector<std::vector<float>> get_stress() const;
  std::vector<std::vector<float>> get_history_vars() const;

  // setter
  void set_is_rigid(bool _is_rigid);
  void add_energy(float _energy);
  void add_stress_mises(float _stress_mises);
  void add_plastic_strain(float _plastic_strain);
  void add_stress(std::vector<float> _stress);
  void add_strain(std::vector<float> _strain);
  void add_history_vars(std::vector<float> vars, size_t iTimestep);

  // clear memory
  void clear_energy();
  void clear_plastic_strain();
  void clear_stress();
  void clear_stress_mises();
  void clear_strain();
  void clear_history_vars();
};

} // namespace qd

#endif
