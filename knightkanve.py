from constraint import Problem, InSetConstraint

def solve_knights_and_knaves(statements):
    problem = Problem()

    # Add variables for each character with domain {0, 1} (0 = Knave, 1 = Knight)
    for character in statements.keys():
        problem.addVariable(character, [0, 1])

    # Add constraints for each statement
    for character, statement in statements.items():
        if statement == "I am a knight.":
            problem.addConstraint(InSetConstraint([1]), [character])
        elif statement == "I am a knave.":
            problem.addConstraint(InSetConstraint([0]), [character])
        elif statement == "I am both a knight and a knave.":
            problem.addConstraint(InSetConstraint([]), [character])

    # Solve the problem
    solutions = problem.getSolutions()

    # Convert solutions to a more readable format
    for solution in solutions:
        for character, value in solution.items():
            solution[character] = "Knight" if value == 1 else "Knave"

    return solutions

# Test the function
statements = {
    "A": "I am a knight.",
    "B": "I am a knave.",
    "C": "I am both a knight and a knave."
}
print(solve_knights_and_knaves(statements))