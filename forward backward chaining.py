
# PR4: Rule-Based Expert System
# Algorithm:
# 1. Store the initial facts and rules.
# 2. Forward chaining derives new facts from existing facts.
# 3. Backward chaining checks whether a goal can be proved.

facts = {"it is raining"}

rules = [
    ("it is raining", "ground is wet"),
    ("ground is wet", "ground is slippery")
]


# Forward Chaining
def forward_chaining(facts, rules): 
    facts = set(facts) 
    print("Forward Chaining:") 
    while True: 
        new_fact = False 
        for condition, conclusion in rules: 
            if condition in facts and conclusion not in facts: 
                facts.add(conclusion) 
                print(condition, "->", conclusion) 
                new_fact = True 
        if not new_fact: 
            break 
    return facts 


# Backward Chaining
def backward_chaining(goal, facts, rules, visited=None):
    if visited is None:
        visited = set()

    # If the goal is already a known fact
    if goal in facts:
        return True

    # Prevent infinite recursion caused by cyclic rules
    if goal in visited:
        return False

    visited.add(goal)

    # Find a rule that can prove the goal
    for condition, conclusion in rules:
        if conclusion == goal:
            if backward_chaining(condition, facts, rules, visited):
                print(condition, "->", conclusion)
                return True

    return False


# Execute Forward Chaining
final_facts = forward_chaining(facts, rules)
print("Final Facts:", final_facts)

# Execute Backward Chaining
goal = "ground is slippery"

print("\nBackward Chaining:")

if backward_chaining(goal, facts, rules):
    print("Goal", goal, "is proved.")
else:
    print("Goal", goal, "cannot be proved.")
