#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <string>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

// Generates a new unique ComponentID
ComponentID GetNewComponentTypeID();

// Returns the unique ComponentID for a given component type
template <typename T> ComponentID GetComponentTypeID() noexcept
{
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
    static ComponentID typeID = GetNewComponentTypeID();
    return typeID;
}

constexpr std::size_t m_MaxComponents = 32;
constexpr std::size_t m_MaxGroups = 32;

using ComponentBitset = std::bitset<m_MaxComponents>;
using GroupBitset = std::bitset<m_MaxGroups>;
using ComponentArray = std::array<Component*, m_MaxComponents>;

// Component Class
class Component
{
public:
    Entity* m_Entity = nullptr;

    virtual void Init() {}
    virtual void Update() {}
    virtual void Draw() {}

    virtual ~Component() {}
};

// Entity Class
class Entity
{
private:
    Manager& m_Manager;
    bool m_IsActive = true;
    std::vector<std::unique_ptr<Component>> m_Component;

    ComponentArray m_ComponentArray;
    ComponentBitset m_ComponentBitset;
    GroupBitset m_GroupBitset;

public:
    // Constructor: Initializes the entity with a reference to the manager
    Entity(Manager& p_Manager);

    void Update();
    void Draw();
    bool IsActive() const;
    void Destroy();
    bool HasGroup(Group p_Group);
    void AddGroup(Group p_Group);
    void DeleteGroup(Group p_Group);

    // Checks if the entity has a specific component
    template <typename T> bool HasComponent() const
    {
        return m_ComponentBitset[GetComponentTypeID<T>()];
    }

    // Adds a component to the entity
    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... p_Args)
    {
        // Create a new component of type T, forwarding the provided arguments to its constructor
        T* c(new T(std::forward<TArgs>(p_Args)...));

        // Set the entity reference in the component
        c->m_Entity = this;

        // Create a unique_ptr to manage the component's memory and add it to the component list
        std::unique_ptr<Component> uPtr{ c };
        m_Component.emplace_back(std::move(uPtr));

        // Store the component in the component array and set the corresponding bit in the bitset
        m_ComponentArray[GetComponentTypeID<T>()] = c;
        m_ComponentBitset[GetComponentTypeID<T>()] = true;

        // Initialize the component
        c->Init();

        // Return a reference to the newly added component
        return *c;
    }

    // Retrieves a component from the entity
    template<typename T> T& GetComponent() const
    {
        auto ptr(m_ComponentArray[GetComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
};

// Manager Class
class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> m_Entities;
    std::array<std::vector<Entity*>, m_MaxGroups> m_GroupedEntities;

public:
    void Update();
    void Draw();
    void Refresh();
    void Clear();
    void AddToGroup(Entity* p_Entity, Group p_Group);
    std::vector<Entity*>& GetGroup(Group p_Group);
    Entity& AddEntity();
};