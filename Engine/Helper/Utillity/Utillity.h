#pragma once

class Utillity
{
public:
    // 리스트를 복사하면서 병합 : O(n)의 시간복잡도
    template <typename T>
    static std::list<T> MergeLists(const std::list<T>& _target1, const std::list<T>& _target2)
    {
        std::vector<T> tempArr;

        tempArr.insert(tempArr.end(), _target1.cbegin(), _target1.cend());
        tempArr.insert(tempArr.end(), _target2.cbegin(), _target2.cend());

        return tempArr;
    }
    // 벡터를 복사하면서 병합
    template <typename T>
    static std::vector<T> MergeVectors(const std::vector<T>& _target1, const std::vector<T>& _target2)
    {
        std::vector<T> tempArr;
        tempArr.reserve(_target1.size() + _target2.size()); // 벡터 크기 미리 예약 (최적화)

        tempArr.insert(tempArr.end(), _target1.begin(), _target1.end());
        tempArr.insert(tempArr.end(), _target2.begin(), _target2.end());

        return tempArr;
    }

    // P클래스를 상속받은 클래스면 true를 반환한다.
    template <typename P, typename C>
    static bool CheckBaseClass(C* _dest) {
        return std::is_base_of<P, C>::value; }
    template <typename P, typename C>
    static bool CheckBaseClass(C _dest) {
        return std::is_base_of<P, C>::value; }

    // Helper class for COM exceptions
    class com_exception : public std::exception
    {
    public:
        com_exception(HRESULT hr) : result(hr) {}

        const char* what() const noexcept override
        {
            static char s_str[64] = {};
            sprintf_s(s_str, "Failure with HRESULT of %08X",
                static_cast<unsigned int>(result));
            return s_str;
        }

    private:
        HRESULT result;
    };

    // Helper utility converts D3D API failures into exceptions.
    static void HR_T(HRESULT hr)
    {
        if (FAILED(hr))
        {
            throw com_exception(hr);
        }
    }
};