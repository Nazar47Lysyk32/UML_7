#include <iostream>
#include <string>

class RegistrationRequest {
public:
    std::string Username;
    int Age;
    // Додайте інші дані, які потрібно обробити
};

class Handler {
protected:
    Handler* NextHandler;

public:
    void SetNextHandler(Handler* nextHandler) {
        NextHandler = nextHandler;
    }

    virtual void ProcessRequest(RegistrationRequest& request) = 0;
};

class AgeHandler : public Handler {
public:
    void ProcessRequest(RegistrationRequest& request) override {
        if (request.Age >= 18) {
            std::cout << "Age verification passed." << std::endl;
            // Викликати наступного обробника у ланцюжку
            if (NextHandler) {
                NextHandler->ProcessRequest(request);
            }
        }
        else {
            std::cout << "Age verification failed. Registration denied." << std::endl;
        }
    }
};

class UsernameHandler : public Handler {
public:
    void ProcessRequest(RegistrationRequest& request) override {
        if (!request.Username.empty()) {
            std::cout << "Username verification passed." << std::endl;
            // Викликати наступного обробника у ланцюжку
            if (NextHandler) {
                NextHandler->ProcessRequest(request);
            }
        }
        else {
            std::cout << "Username verification failed. Registration denied." << std::endl;
        }
    }
};

int main() {
    // Створення обробників
    Handler* ageHandler = new AgeHandler();
    Handler* usernameHandler = new UsernameHandler();

    // Налаштування ланцюжка
    ageHandler->SetNextHandler(usernameHandler);

    // Створення запиту на реєстрацію
    RegistrationRequest request;
    request.Username = "JohnDoe";
    request.Age = 25;
    // Додайте інші дані за необхідності

    // Початок обробки ланцюжка
    ageHandler->ProcessRequest(request);

    // Очищення пам'яті
    delete ageHandler;
    delete usernameHandler;

    return 0;
}
