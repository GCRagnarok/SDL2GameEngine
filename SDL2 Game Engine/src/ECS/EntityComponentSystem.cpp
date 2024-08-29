#include "../../include/ECS/EntityComponentSystem.h"

// Generates a new unique ComponentID
ComponentID GetNewComponentTypeID()
{
    static ComponentID lastID = 0u;
    return lastID++;
}

// Entity Class Implementation
Entity::Entity(Manager& p_Manager) : m_Manager(p_Manager)
{
    m_ComponentArray = {};
}

void Entity::Update()
{
    for (auto& c : m_Component) c->Update();
}

void Entity::Draw()
{
    for (auto& c : m_Component) c->Draw();
}

bool Entity::IsActive() const { return m_IsActive; }

void Entity::Destroy() { m_IsActive = false; }

bool Entity::HasGroup(Group p_Group)
{
    return m_GroupBitset[p_Group];
}

void Entity::AddGroup(Group p_Group)
{
    m_GroupBitset[p_Group] = true;
    m_Manager.AddToGroup(this, p_Group);
}

void Entity::DeleteGroup(Group p_Group)
{
    m_GroupBitset[p_Group] = false;
}

// Manager Class Implementation
void Manager::Update()
{
    for (auto& e : m_Entities) e->Update();
}

void Manager::Draw()
{
    for (auto& e : m_Entities) e->Draw();
}

void Manager::Refresh()
{
    // Iterate through each group
    for (auto i(0u); i < m_MaxGroups; i++)
    {
        auto& v = m_GroupedEntities[i];

        // Remove entities from the group that are either inactive or no longer belong to the group
        v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* p_Entity)
            {
                return !p_Entity->IsActive() || !p_Entity->HasGroup(i);
            }), std::end(v));
    }

    // Remove inactive entities from the main entity list
    m_Entities.erase(std::remove_if(std::begin(m_Entities), std::end(m_Entities), [](const std::unique_ptr<Entity>& p_Entity)
        {
            return !p_Entity->IsActive();
        }), std::end(m_Entities));
}

void Manager::Clear()
{
    m_Entities.clear();
    for (auto& group : m_GroupedEntities)
    {
        group.clear();
    }
}

void Manager::AddToGroup(Entity* p_Entity, Group p_Group)
{
    m_GroupedEntities[p_Group].emplace_back(p_Entity);
}

std::vector<Entity*>& Manager::GetGroup(Group p_Group)
{
    return m_GroupedEntities[p_Group];
}

Entity& Manager::AddEntity()
{
    // Create a new entity and pass a reference to the manager
    Entity* e = new Entity(*this);

    // Create a unique_ptr to manage the entity's memory and add it to the entity list
    std::unique_ptr<Entity> uPtr{ e };
    m_Entities.emplace_back(std::move(uPtr));

    // Return a reference to the newly added entity
    return *e;
}