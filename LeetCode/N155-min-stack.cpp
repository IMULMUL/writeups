struct NodeElt {
    int val;
    struct NodeElt* next;
    NodeElt(int val) : val(val), next(nullptr) {
    }
};

class MinStack {
public:
    /** initialize your data structure here. */
    using Node = NodeElt*;
    Node head;
    MinStack() {
        this->head = NULL;
    }
    
    void push(int x) {
        Node tmp = new NodeElt(x);
        tmp->next = this->head;
        this->head = tmp;
    }
    
    void pop() {
        Node tmp = this->head;
        this->head = tmp->next;
        delete tmp;
    }
    
    int top() {
        return this->head->val;
    }
    
    int getMin() {
        int min = this->head->val;
        for (Node tmp = this->head; tmp != NULL; tmp = tmp->next) {
            if (tmp->val < min)
                min = tmp->val;
        }
        
        return min;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
