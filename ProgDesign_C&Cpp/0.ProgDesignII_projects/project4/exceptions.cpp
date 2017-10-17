#include <string>

using namespace std;

class Library_Base_Exception {
  public:
    virtual std::string what() = 0;
};

class JsonReadError : public Library_Base_Exception {
  public:
    virtual std::string what() {
        return std::string("JsonReadError");
    }
};

class Num_Error : public Library_Base_Exception {
  public:
    virtual std::string what() {
        return std::string("Num_Error");
    }
};
class Negative_Books_Num : public Num_Error {
  public:
    virtual std::string what() {
        return std::string("Negative_Books_Num");
    }
};

class ElementDuplicated : public Library_Base_Exception {
  public :
    virtual std::string what() {
        return string("ElementDuplicated");
    }
};
class UserDuplicated : public ElementDuplicated {
  public:
    virtual std::string what() {return string("UserDuplicated");}
};
class ISBNDuplicated : public ElementDuplicated {
  public:
    virtual std::string what() {
        return string("ISBNDuplicated");
    }
};

class ElementNotFound : public Library_Base_Exception {
  public:
    virtual std::string what() {
        return string("ElementNotFound");
    }
};
class UserNotFound : public ElementNotFound {
  public:
    virtual std::string what() {return string("UserNotFound");}
};
class BookNotFound : public ElementNotFound {
  public :
    virtual std::string what() {
        return string("BookNotFound");
    }
};

class InvalidInput : public Library_Base_Exception {
  public:
    virtual std::string what() {
        return string("InvalidInput");
    }
};
class InvalidUserName : public InvalidInput {
  public:
    virtual std::string what() {return string("InvalidUserName");}
};
class InvalidPassword : public InvalidInput {
  public:
    virtual std::string what() {return string("InvalidPassword");}
};
class BookNumInvalid : public InvalidInput {
  public:
    virtual std::string what() {
        return string("BookNumInvalid");
    }
};
class UserGroupError : public InvalidInput {
  public:
    virtual string what() {
        return string("UserGroupError");
    }
};

class IndexOverflow : public Library_Base_Exception {
  public:
    virtual std::string what() {
        return string("IndexOverflow");
    }
};
/* NOTES : exceptions to create
* BookNotFound
* UserNotFound
* BookNumInvalid
* UserDuplicated
* IndexOverflow
*/
