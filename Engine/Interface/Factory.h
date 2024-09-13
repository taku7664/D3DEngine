#pragma once

namespace Engine
{
    _ABSTRACT Factory
    {
    public:
    protected:
        template<typename T, typename... Args>
        T* Create(Args&&... args)
        {
            static_assert(std::is_base_of<Factory, T>::value, "Create_Fail");
            T* instance = new T(std::forward<Args>(args)...);
            m_watingCreations.push_back(instance);
            return instance;
        }
        void CreateUpdate();
        void DestroyUpdate();
        std::vector<Entity*> m_watingCreations;
        std::vector<Entity*> m_watingDestructions;
    private:
    };
}
