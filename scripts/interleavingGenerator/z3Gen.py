from z3 import *

def interleaving_with_constraints(number_list):
# Create Z3 solver
  solver = Solver()

  # Create variables for each number in the list
  numbers = [Int(f"num{i}") for i in range(len(number_list))]

  # Add constraints to ensure each number is selected from the list
  for i, number in enumerate(numbers):
      solver.add(Or([number == n for n in number_list]))

   # Adding a constraint for clause1
  clause1_low = number_list.index(1)
  clause1_high = number_list.index(2)
  solver.add(numbers[clause1_low] < numbers[clause1_high])

   # Adding a constraint for clause2
  clause2_low = number_list.index(2)
  clause2_high = number_list.index(3)
  solver.add(numbers[clause2_low] < numbers[clause2_high])

   # Adding a constraint for clause3
  clause3_low = number_list.index(5)
  clause3_high = number_list.index(6)
  solver.add(numbers[clause3_low] < numbers[clause3_high])

   # Adding a constraint for clause4
  clause4_low = number_list.index(5)
  clause4_high = number_list.index(7)
  solver.add(numbers[clause4_low] < numbers[clause4_high])

   # Adding a constraint for clause5
  clause5_low = number_list.index(1)
  clause5_high = number_list.index(5)
  solver.add(numbers[clause5_low] < numbers[clause5_high])

   # Adding a constraint for clause6
  clause6_low = number_list.index(3)
  clause6_high = number_list.index(5)
  solver.add(numbers[clause6_low] < numbers[clause6_high])

  # Initialize counter for generated numbers
  count = 0

# Check if the constraints are satisfiable
  while solver.check() == sat and count < 50:
      # Get the satisfying model
      model = solver.model()
      # Extract the selected numbers from the model
      selected_numbers = [model.evaluate(number).as_long() for number in numbers]
      yield selected_numbers
      # Increment counter
      count += 1
      # Add a new constraint to exclude the current solution
      solver.add(Or([numbers[i] != selected_numbers[i] for i in range(len(number_list))]))

# ID of interacting agents from configuration file
number_list = [1, 2, 3, 4, 5, 6, 7]

# Generate and write 50 interleavings to interleavings.txt
interleavingFile = "interleavings.txt"
file = os.path.join(interleavingFile)
with open(file, "w") as handle: 
  for number in interleaving_with_constraints(number_list):
      sequence = str(number) + "\n"
      handle.write(sequence)
