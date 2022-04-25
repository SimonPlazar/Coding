#include <iostream>
#include <stack>

void printStack(std::stack<int> stacks[]) {
    for (int i = 0; i < 3; i++) {
        std::cout << "------------------------------\nStack" << i+1 << ": \n";
        for (std::stack<int> dump = stacks[i]; !dump.empty(); dump.pop()){
            for (int j = 0; j < dump.top(); ++j) {
                std::cout << "*";
            }
            std::cout << "\n";
        }
    }
    std::cout << "------------------------------\n";
}

void initStack(std::stack<int> &stack, int value) {
    for (int i = 0; i < value; i++) {
        stack.push(value - i);
    }
}

void moveTop(std::stack<int> &stack1, std::stack<int> &stack2) {
    if (stack1.empty())
        std::cout << "Error: Empty" << std::endl;
    else if (stack2.empty() || stack1.top() < stack2.top()) {
        stack2.push(stack1.top());
        stack1.pop();
    } else
        std::cout << "Error: Size" << std::endl;

}

bool checkEnd(std::stack<int> stacks[], int poskusi) {
    if ((stacks[0].empty() && stacks[1].empty()) || (stacks[0].empty() && stacks[2].empty())) {
        printStack(stacks);
        std::cout << "Konec! \n St poskusov: " << poskusi << std::endl;
        return false;
    } else
        return true;
}

int main() {
    std::stack<int> stacks[3];
    int x;
    int choice1;
    int choice2;
    bool flag;
    int poskusi = 0;

    std::cout << "Podaj st ploscic: ";
    std::cin >> x;

    initStack(stacks[0], x);

    do {
        printStack(stacks);

        std::cout << "Izberi stack: ";
        std::cin >> choice1;

        std::cout << "Izberi stack: ";
        std::cin >> choice2;

        if (choice1 > 3 || choice2 > 3)
            std::cout << "Error: out of bounds" << std::endl;
        else if (choice1 == choice2)
            std::cout << "Error: same stack" << std::endl;
        else
            moveTop(stacks[choice1-1], stacks[choice2-1]);

        poskusi++;

        flag = checkEnd(stacks, poskusi);
    } while (flag);
    return 0;
}
