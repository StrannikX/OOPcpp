# ifndef CONTAINER_HPP
# define CONTAINER_HPP

# include <cstddef>
# include <exception>

template<class T> class ContainerIterator;

template<class T> class Container {
public:

    Container() {
        size = 0;
        head = tail = nullptr;
    }

    Container(Container<T> const& container) {
        ContainerIterator<T> it(container);
        while (it) {
            append(*it);
            it++;
        }
    }

    Container& operator=(Container const& container) {
        ContainerIterator<T> it(container);
        while (it) {
            append(*it);
            it++;
        }
        return *this;
    }

    // Размер списка
    unsigned getSize() const {
        if (size == 0) throw std::out_of_range("Container is empty");
        return size;
    }

    T getFirst() const {
        if (size == 0) throw std::out_of_range("Container is empty");
        return head->value;
    }

    T getLast() const {
        return tail->value;
    }

    // Добавить значение в конец
    void append(T value) {
        Node * node = new Node(value);
        if (size == 0) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        size++;
    }

    // Добавить в начало
    void prepend(T value) {
        Node * node = new Node(value);
        node->next = head;
        head = node;
        size++;
    }

    // Удалить с конца и вернуть значение
    T pop() {
        if (size == 0) throw std::out_of_range("Container is empty");

        Node * node = head;
        if (size == 1) {
            node = head;
            head = nullptr;
        } else {
            Node * tmp = head;
            for (; tmp->next->next != nullptr; tmp = tmp->next);
            node = tmp->next;
            tmp->next = nullptr;
        }
        T val = node->value;
        delete node;

        size--;

        return val;
    }

    // Удалить из начала и вернуть значение
    T shift() {
        if (size == 0) throw std::out_of_range("Container is empty");
        Node * node = head;
        head = node->next;

        size--;

        T val = node->value;
        delete node;
        return val;
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return size == 0;
    }

    void clear() {
        Node * node = head;
        while (node != nullptr) {
            Node * tmp = node;
            node = node->next;
            delete tmp;
        }
        head = tail = nullptr;
    }

    // Деструктор, удаляет узлы списка
    ~Container() {
        clear();
    }

private:

    class Node {
    public:
        Node(T value) {
            this->value = value;
            this->next = nullptr;
        }

        T value;
        Node * next;
    };

    Node * head;
    Node * tail;
    unsigned size;

    friend ContainerIterator<T>;
};


template <class T> class ContainerIterator {
    typename Container<T>::Node * node;

public:
    ContainerIterator(Container<T> const &container) {
        node = container.head;
    }

    bool hasNext() const {
        return node != nullptr;
    }

    // Приведение к bool
    // Если обход окончен - то false, нет - true
    operator bool() {
        return node != nullptr;
    }

    ContainerIterator& next() {
        if (node == nullptr) throw std::out_of_range("Iterator reached the end of Container");
        node = node->next;
        return *this;
    }

    // Сдвинуть итератор на один элемент
    ContainerIterator& operator++() {
        return next();
    }

    // Сдвинуть итератор на один элемент (постфикснаяя форма)
    ContainerIterator& operator++(int) {
        return next();
    }

    T& value() {
        return node->value;
    }

    // Получить значение текущего узла
    T& operator*() {
        return node->value;
    }

    void reset(Container<T> const &container) {
        node = container.head;
    }
};

# endif // CONTAINER_HPP
