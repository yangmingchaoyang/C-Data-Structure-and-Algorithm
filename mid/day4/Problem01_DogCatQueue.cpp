/*
宠物、狗和猫的类如下:
public static class Pet {
private String type;
public Pet(String type) {
this.type = type;
}
public String getPetType() {
return this.type;
}
}
public static class Dog extends Pet {
public Dog() {
super("dog");
}
}
public static class Cat extends Pet {
public Cat() {
super("cat");
}
}

实现一种狗猫队列的结构，要求如下:
用户可以调用add方法将cat类或dog类的 实例放入队列中;
用户可以调用pollAll方法，将队列中所有的实例按照进队列 的先后顺序依次弹出;
用户可以调用pollDog方法，将队列中dog类的实例按照 进队列的先后顺序依次弹出;
用户可以调用pollCat方法，将队列中cat类的实 例按照进队列的先后顺序依次弹出;
用户可以调用isEmpty方法，检查队列中是 否还有dog或cat的实例;
用户可以调用isDogEmpty方法，检查队列中是否有dog 类的实例;
用户可以调用isCatEmpty方法，检查队列中是否有cat类的实例。
要求以上所有方法时间复杂度都是O(1)的
*/

#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>

class Pet {
private:
    std::string type;

public:
    Pet(std::string type) : type(type) {}

    std::string getPetType() {
        return this->type;
    }
};

class Dog : public Pet {
public:
    Dog() : Pet("dog") {}
};

class Cat : public Pet {
public:
    Cat() : Pet("cat") {}
};

class PetEnterQueue {
private:
    Pet pet;
    long count;

public:
    PetEnterQueue(Pet pet, long count) : pet(pet), count(count) {}

    Pet getPet() {
        return this->pet;
    }

    long getCount() {
        return this->count;
    }

    std::string getEnterPetType() {
        return this->pet.getPetType();
    }
};

class DogCatQueue {
private:
    std::queue<PetEnterQueue> dogQ;
    std::queue<PetEnterQueue> catQ;
    long count;

public:
    DogCatQueue() : count(0) {}

    void add(Pet pet) {
        if (pet.getPetType() == "dog") {
            this->dogQ.push(PetEnterQueue(pet, this->count++));
        } else if (pet.getPetType() == "cat") {
            this->catQ.push(PetEnterQueue(pet, this->count++));
        } else {
            throw std::runtime_error("err, not dog or cat");
        }
    }

    Pet pollAll() {
        if (!this->dogQ.empty() && !this->catQ.empty()) {
            if (this->dogQ.front().getCount() < this->catQ.front().getCount()) {
                PetEnterQueue petQueue = this->dogQ.front();
                this->dogQ.pop();
                return petQueue.getPet();
            } else {
                PetEnterQueue petQueue = this->catQ.front();
                this->catQ.pop();
                return petQueue.getPet();
            }
        } else if (!this->dogQ.empty()) {
            PetEnterQueue petQueue = this->dogQ.front();
            this->dogQ.pop();
            return petQueue.getPet();
        } else if (!this->catQ.empty()) {
            PetEnterQueue petQueue = this->catQ.front();
            this->catQ.pop();
            return petQueue.getPet();
        } else {
            throw std::runtime_error("err, queue is empty!");
        }
    }

    Pet pollDog() {
        if (!this->isDogQueueEmpty()) {
            PetEnterQueue petQueue = this->dogQ.front();
            this->dogQ.pop();
            return petQueue.getPet();
        } else {
            throw std::runtime_error("Dog queue is empty!");
        }
    }

    Pet pollCat() {
        if (!this->isCatQueueEmpty()) {
            PetEnterQueue petQueue = this->catQ.front();
            this->catQ.pop();
            return petQueue.getPet();
        } else {
            throw std::runtime_error("Cat queue is empty!");
        }
    }

    bool isEmpty() {
        return this->dogQ.empty() && this->catQ.empty();
    }

    bool isDogQueueEmpty() {
        return this->dogQ.empty();
    }

    bool isCatQueueEmpty() {
        return this->catQ.empty();
    }
};

int main() {
    DogCatQueue test;

    Pet dog1 = Dog();
    Pet cat1 = Cat();
    Pet dog2 = Dog();
    Pet cat2 = Cat();
    Pet dog3 = Dog();
    Pet cat3 = Cat();

    test.add(dog1);
    test.add(cat1);
    test.add(dog2);
    test.add(cat2);
    test.add(dog3);
    test.add(cat3);

    test.add(dog1);
    test.add(cat1);
    test.add(dog2);
    test.add(cat2);
    test.add(dog3);
    test.add(cat3);

    test.add(dog1);
    test.add(cat1);
    test.add(dog2);
    test.add(cat2);
    test.add(dog3);
    test.add(cat3);

    while (!test.isDogQueueEmpty()) {
        std::cout << test.pollDog().getPetType() << std::endl;
    }

    while (!test.isEmpty()) {
        std::cout << test.pollAll().getPetType() << std::endl;
    }

    return 0;
}