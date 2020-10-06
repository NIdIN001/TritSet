#ifndef LAB1_TRITSET_H
#define LAB1_TRITSET_H

#include <iostream>
#include <cmath>
#include <unordered_map>
#include <utility>

using namespace std;

/*
 В 1 uint (unsigned int) помещается 16 тритов

 Пратформозависимость:
 16 == (8 * sizeof(unsigned int) / 2)
*/


enum class Trit: unsigned int {
    UNKNOWN = 0u, // -- 00
    FALSE = 1u,   // -- 01
    TRUE = 3u     // -- 11
};

class TritSet {
private:
    unsigned int *data;
    size_t count;

    class Ttrit {
    private:
        TritSet &set;
        size_t current_index;

    public:
        Ttrit(TritSet &set, size_t current_index);
        ~Ttrit();
        explicit operator Trit() const;
        const TritSet &get_set();
        [[nodiscard]] size_t get_current_index() const;
        Trit operator|(const Trit &t) const;
        Trit operator|(const Ttrit &t) const;
        Trit operator&(const Trit &t) const;
        Trit operator&(const Ttrit &t) const;
        Trit operator!() const;
        bool operator==(const Trit &t) const;
        bool operator==(const Ttrit &t) const;
        bool operator!=(const Trit &t) const;
        bool operator!=(const Ttrit &t) const;
        Ttrit &operator=(const Trit &t);
        Ttrit &operator=(const Ttrit &t);
    };

public:
    explicit TritSet(size_t count_of_trit);
    TritSet(TritSet &other);
    TritSet(TritSet &&other) noexcept;
    ~TritSet();
    Ttrit operator[](size_t index);
    TritSet operator&(const TritSet &second);
    TritSet operator|(const TritSet &second);
    TritSet operator!();
    [[nodiscard]] size_t cardinality(Trit value) const;
    [[nodiscard]] std::unordered_map<Trit, int> cardinality() const;
    void trim(size_t last_index);
    [[nodiscard]] size_t length() const;
    void shrink();

    //private:
    [[nodiscard]] size_t capacity() const; //подсчет необходимого кол-ва uint для хранения count тритов
    static size_t capacity(size_t count);
    void set_value(unsigned int index, Trit value);
    [[nodiscard]] Trit get_value(unsigned int index) const;
    void resize(size_t new_count);
    friend ostream &operator<<(ostream &out, TritSet::Ttrit t);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [[nodiscard]] unsigned int* get_data() const;
    [[nodiscard]] size_t get_count() const;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
};


#endif //LAB1_TRITSET_H
