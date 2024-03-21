from z3 import *

def main():
    # Define variables
    nums = [Int(f"num{i}") for i in range(6)]

    # Each num[i] should be between 0 and 9
    constraints = [And(0 <= nums[i], nums[i] <= 9) for i in range(6)]

    # 1 occurs once
    constraints.append(Sum([If(nums[i] == 1, 1, 0) for i in range(6)]) == 1)

    # 3 never occurs before 1
    constraints.append(Or(nums[0] != 3, nums[1] == 1))

    # Create solver
    solver = Solver()
    solver.add(constraints)

    # Iterate over solutions
    while solver.check() == sat:
        model = solver.model()
        solution = [model.evaluate(nums[i]).as_long() for i in range(6)]
        print(solution)
        solver.add(Or([nums[i] != model.evaluate(nums[i]) for i in range(6)]))

if __name__ == "__main__":
    main()
