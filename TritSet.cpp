#include "TritSet.h"

Trit operator!(Trit value) {
    switch (value) {
        case Trit::TRUE:
            return Trit::FALSE;
        case Trit::UNKNOWN:
            return Trit::UNKNOWN;
        case Trit::FALSE:
            return Trit::TRUE;
    }
}

Trit operator&(Trit first,Trit second) {
    switch (first) {
        case Trit::FALSE:
            switch (second) {
                case Trit::FALSE:
                case Trit::UNKNOWN:
                case Trit::TRUE:
                    return Trit::FALSE;
            }
        case Trit::UNKNOWN:
            switch (second) {
                case Trit::FALSE:
                    return Trit::FALSE;
                case Trit::UNKNOWN:
                case Trit::TRUE:
                    return Trit::UNKNOWN;
            }
        case Trit::TRUE:
            switch (second) {
                case Trit::FALSE:
                    return Trit::FALSE;
                case Trit::UNKNOWN:
                    return Trit::UNKNOWN;
                case Trit::TRUE:
                    return Trit::TRUE;
            }
    }
}

Trit operator|(Trit first,Trit second) {
    switch (first) {
        case Trit::FALSE:
            switch (second) {
                case Trit::FALSE:
                    return Trit::FALSE;
                case Trit::UNKNOWN:
                    return Trit::UNKNOWN;
                case Trit::TRUE:
                    return Trit::TRUE;
            }
        case Trit::UNKNOWN:
            switch (second) {
                case Trit::FALSE:
                case Trit::UNKNOWN:
                    return Trit::UNKNOWN;
                case Trit::TRUE:
                    return Trit::TRUE;
            }
        case Trit::TRUE:
            switch (second) {
                case Trit::FALSE:
                case Trit::UNKNOWN:
                case Trit::TRUE:
                    return Trit::TRUE;
            }
    }
    return Trit::UNKNOWN;
}

std::ostream& operator<<(std::ostream& out, Trit value) {
    switch (value) {
        case Trit::UNKNOWN:
            return out << "UNKNOWN";
        case Trit::FALSE:
            return out << "FALSE";
        case Trit::TRUE:
            return out << "TRUE";
    }
    return out << "UNKNOWN";
}

TritSet::Ttrit::Ttrit(TritSet &set, size_t current_index)  : set(set), current_index(current_index) {}

TritSet::Ttrit::~Ttrit() = default;

TritSet::Ttrit::operator Trit() const {
    if (current_index >= set.count)
        return Trit::UNKNOWN;
    else
        return set.get_value(current_index);
}

const TritSet &TritSet::Ttrit::get_set() {
    return set;
}

size_t TritSet::Ttrit::get_current_index() const {
    return current_index;
}

Trit TritSet::Ttrit::operator|(const Trit &trit) const {
    if (current_index >= set.count)
        return Trit::UNKNOWN;
    else
        return trit | set.get_value(current_index);
}

Trit TritSet::Ttrit::operator|(const TritSet::Ttrit &trit) const {
    if (current_index >= set.count)
        return Trit::UNKNOWN;
    else
        return trit | set.get_value(current_index);
}

Trit TritSet::Ttrit::operator&(const Trit &trit) const {
    if (current_index >= set.count)
        return Trit::UNKNOWN;
    else
        return trit & set.get_value(current_index);
}

Trit TritSet::Ttrit::operator&(const TritSet::Ttrit &trit) const {
    if (current_index >= set.count)
        return Trit::UNKNOWN;
    else
        return trit & set.get_value(current_index);
}

Trit TritSet::Ttrit::operator!() const {
    if (current_index >= set.count)
        return Trit::UNKNOWN;
    else
        return !set.get_value(current_index);
}

bool TritSet::Ttrit::operator==(const Trit &trit) const {
    if (current_index >= set.count)
        return Trit::UNKNOWN == trit;
    else
        return trit == set.get_value(current_index);
}

bool TritSet::Ttrit::operator==(const TritSet::Ttrit &trit) const {
    if (current_index >= set.count)
        return false;
    else
        return trit == set.get_value(current_index);
}

bool TritSet::Ttrit::operator!=(const Trit &trit) const {
    if (current_index >= set.count)
        return false;
    else
        return trit != set.get_value(current_index);
}

bool TritSet::Ttrit::operator!=(const TritSet::Ttrit &trit) const {
    if (current_index >= set.count)
        return false;
    else
        return trit != set.get_value(current_index);
}

TritSet::Ttrit &TritSet::Ttrit::operator=(const Trit &trit) {
    if (current_index >= set.count) {
        if (trit != Trit::UNKNOWN && current_index >= set.count) {
            set.resize(current_index);
        }
    } else
        set.set_value(current_index, trit);
    return *this;
}

TritSet::Ttrit &TritSet::Ttrit::operator=(const TritSet::Ttrit &trit) {
    if (trit != Trit::UNKNOWN && current_index >= set.count) {
        set.resize(current_index);
    } else {
        set.set_value(current_index, (Trit) trit);
    }
    return *this;
}

TritSet::TritSet(size_t count_of_trit) {
    count = count_of_trit;
    data = new unsigned int[capacity()];

    memset(data, 0, capacity() * sizeof(unsigned int));
}

TritSet::TritSet(TritSet &other) {
    data = other.data;
    count = other.count;
}

TritSet::TritSet(TritSet &&other) noexcept: data(nullptr), count(0) {
    data = other.data;
    count = other.count;

    other.data = nullptr;
    other.count = 0;
}

TritSet::~TritSet() {
    delete[] data;
}

TritSet::Ttrit TritSet::operator[](size_t index) {
    Ttrit a(*this, index);
    return a;
}

TritSet TritSet::operator&(const TritSet &second) {
    size_t first_capacity = this->capacity();
    size_t second_capacity = second.capacity();

    TritSet result(this->count > second.count ? this->count : second.count);
    std::memcpy(result.data,
                this->count > second.count ? this->data : second.data,
                result.capacity() * sizeof(unsigned int));

    for (int i = 0; i < (this->count > second.count ? second_capacity : first_capacity); i++) {
        result.data[i] &= (this->count > second.count ? second.data[i] : this->data[i]);
    }
    return result;
}

TritSet TritSet::operator|(const TritSet &second) {
    size_t first_capacity = this->capacity();
    size_t second_capacity = second.capacity();

    TritSet result(this->count > second.count ? this->count : second.count);
    std::memcpy(result.data,
                this->count > second.count ? this->data : second.data,
                result.capacity() * sizeof(unsigned int));

    for (int i = 0; i < (this->count > second.count ? second_capacity : first_capacity); i++) {
        result.data[i] |= (this->count > second.count ? second.data[i] : this->data[i]);
    }
    return result;
}

TritSet TritSet::operator!() {
    TritSet result(this->count);
    std::memcpy(result.data,
                this->data,
                result.capacity() * sizeof(unsigned int));

    for (int i = 0; i < this->count; i++) {
        result[i] = !result[i];
    }
    return result;
}

size_t TritSet::cardinality(Trit value) const {
    unsigned int current_uint = 0;
    unsigned int current_trit = 0;
    size_t result = 0;

    while (current_uint * (8 * sizeof(unsigned int) / 2) + current_trit < this->count) {
        if (get_value(current_uint * (8 * sizeof(unsigned int) / 2) + current_trit) == value) {
            result++;
        }

        current_trit++;
        if (current_trit == (8 * sizeof(unsigned int) / 2)) {
            current_uint++;
            current_trit = 0;
        }
    }
    return result;
}

std::unordered_map<Trit, int> TritSet::cardinality() const {
    unordered_map<Trit, int> information;
    information.insert(make_pair<Trit, int>(Trit::TRUE, cardinality(Trit::TRUE)));
    information.insert(make_pair<Trit, int>(Trit::FALSE, cardinality(Trit::FALSE)));
    information.insert(make_pair<Trit, int>(Trit::UNKNOWN, cardinality(Trit::UNKNOWN)));

    return information;
}

void TritSet::trim(size_t last_index) {
    unsigned int current_trit = last_index / (8 * sizeof(unsigned int) / 2);
    unsigned int capacity = this->capacity();
    while (last_index < ((8 * sizeof(unsigned int) / 2) - 1)) {
        set_value(last_index, Trit::UNKNOWN);
        last_index++;
    }
    while (current_trit < capacity) {
        data[current_trit] = 0u;
        current_trit++;
    }
}

size_t TritSet::length() const {
    size_t current_uint = count / 16;
    size_t current_trit = (count % 16) - 1;
    while (get_value(current_uint * (8 * sizeof(unsigned int) / 2) + current_trit) == Trit::UNKNOWN) {
        if (current_trit == 0) {
            current_trit = ((8 * sizeof(unsigned int) / 2) - 1);
            current_uint--;
            if (current_uint == -1) {
                return 0;
            }
            continue;
        }
        current_trit--;
    }
    return current_uint * (8 * sizeof(unsigned int) / 2) + current_trit + 1;
}

size_t TritSet::capacity() const { //подсчет необходимого кол-ва uint для хранения count тритов
    return ceil(count * 2.0 / 8.0 / sizeof(unsigned int));
}

void TritSet::set_value(unsigned int index, Trit value) {
    unsigned int current_uint = index / (8 * sizeof(unsigned int) / 2);
    unsigned int current_trit = index % (8 * sizeof(unsigned int) / 2);
    unsigned int iValue = 0;

    switch (value) {            //Интерпретирование значений Trit:: в uint
        case Trit::UNKNOWN:
            iValue = 0u;
            break;
        case Trit::FALSE:
            iValue = 1u;
            break;
        case Trit::TRUE:
            iValue = 3u;
            break;
    }

    switch (iValue) {
        case 0u:
            data[current_uint] &= ~(1u << ((((8 * sizeof(unsigned int) / 2) - 1) - current_trit) * 2));
            //ставит второй бит трита
            data[current_uint] &= ~(1u << (((((8 * sizeof(unsigned int) / 2) - 1) - current_trit) * 2) + 1));
            //ставит первый бит трита
            break;
        case 1u:
        case 2u:
            data[current_uint] |= (1u << ((((8 * sizeof(unsigned int) / 2) - 1) - current_trit) * 2));
            //ставит 1
            data[current_uint] &= ~(1u << (((((8 * sizeof(unsigned int) / 2) - 1) - current_trit) * 2) + 1));
            //ставит 0
            break;
        case 3u:
            data[current_uint] |= (1u << ((((8 * sizeof(unsigned int) / 2) - 1) - current_trit) * 2));
            data[current_uint] |= (1u << (((((8 * sizeof(unsigned int) / 2) - 1) - current_trit) * 2) + 1));
            break;
        default:
            break;
    }
}

Trit TritSet::get_value(unsigned int index) const {
    unsigned int current_uint = index / (8 * sizeof(unsigned int) / 2);
    unsigned int current_trit = index % (8 * sizeof(unsigned int) / 2);
    unsigned int copy_of_uint = data[current_uint];

    unsigned int value = 3u & (copy_of_uint >> ((((8 * sizeof(unsigned int) / 2) - 1) - current_trit) * 2));
    //чтение 2 нужних битов

    switch (value) {
        case (0u):
            return Trit::UNKNOWN;
        case (1u):
            return Trit::FALSE;
        case (3u):
            return Trit::TRUE;
        default:
            return Trit::UNKNOWN;
    }
}

ostream &operator<<(ostream &out, TritSet::Ttrit trit) {
    if (trit.get_current_index() >= trit.get_set().count)
        return out << Trit::UNKNOWN;
    else
        return out << trit.get_set().get_value(trit.get_current_index());
}

size_t TritSet::capacity(size_t count) {
    return ceil(count * 2.0 / 8.0 / sizeof(unsigned int));
}

void TritSet::resize(size_t new_count) {
    unsigned int *new_data = new unsigned int[capacity(new_count)];
    //std::memset(new_data, 0, capacity(new_count) * sizeof(unsigned int));
    if (new_count > count) {
        std::memcpy(new_data, data, capacity(count) * sizeof(unsigned int));
    } else {
        std::memcpy(new_data, data, capacity(new_count) * sizeof(unsigned int));
    }
    free(this->data);

    this->data = new_data;
    this->count = new_count;
}

void TritSet::shrink() {
    int not_a_unkn = length();
    if (not_a_unkn != 0) {
        resize(not_a_unkn);
    }
}

unsigned int *TritSet::get_data() const {
    return this->data;
}

size_t TritSet::get_count() const {
    return this->count;
}
