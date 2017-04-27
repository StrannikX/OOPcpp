# ifndef BASE_HPP
# define BASE_HPP

# include <string>

class Printable {
public:
    virtual std::string  print() const = 0;
};

class Named: public Printable {
public:
    Named(std::string const& name) {
        this->name = name;
    }

    std::string const& getName() const {
        return name;
    }

    virtual std::string print() const {
        return name;
    }
private:
    std::string name;
};

# endif // BASE_HPP
