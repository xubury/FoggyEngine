#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <algorithm>
#include <queue>
namespace foggy {

template <typename T, class Container = std::vector<T>,
          class Compare = std::less<typename Container::value_type>>
class PriorityQueue : public std::priority_queue<T, Container, Compare> {
   public:
    bool remove(const T &value);
    template <class Predicate>
    bool remove(Predicate pred);
};

template <typename T, class Container, class Compare>
bool PriorityQueue<T, Container, Compare>::remove(const T &value) {
    auto it = std::find(this->c.begin(), this->c.end(), value);
    if (it != this->c.end()) {
        this->c.erase(it);
        std::make_heap(this->c.begin(), this->c.end(), this->comp);
        return true;
    } else {
        return false;
    }
}

template <typename T, class Container, class Compare>
template <class Predicate>
bool PriorityQueue<T, Container, Compare>::remove(Predicate pred) {
    auto it = std::remove_if(this->c.begin(), this->c.end(), pred);
    if (it != this->c.end()) {
        this->c.erase(it, this->c.end());
        std::make_heap(this->c.begin(), this->c.end(), this->comp);
        return true;
    } else {
        return false;
    }
}

}  // namespace foggy

#endif /* PRIORITYQUEUE_H */
