import math
import pandas as pd
import os
import nbformat as nbf
import matplotlib.pyplot as plt

class Ulam:
    def __init__(self, n):
        num = n * n
        self.primes = self.sieve(num)
        self.size = n
        self.matrix = [[0 for _ in range(n)] for _ in range(n)]
        self.generate_spiral(num)

    def sieve(self, num):
        prime = [True] * (num + 1)
        for p in range(2, int(math.sqrt(num)) + 1):
            if prime[p]:
                for i in range(p * p, num + 1, p):
                    prime[i] = False
        return prime

    def generate_spiral(self, num):
        x, y = self.size // 2, self.size // 2
        dirs = [(0, 1), (-1, 0), (0, -1), (1, 0)]  # Right, Up, Left, Down
        dir_idx = 0
        steps = 1
        val = 1

        while val <= num:
            for _ in range(steps):
                if 0 <= x < self.size and 0 <= y < self.size:
                    self.matrix[x][y] = val
                    val += 1
                    if val > num:
                        break
                x += dirs[dir_idx][0]
                y += dirs[dir_idx][1]

            dir_idx = (dir_idx + 1) % 4
            if dir_idx == 0 or dir_idx == 2:
                steps += 1

    def max_diagonal_sequence(self):
        max_seq = 0

        # Check diagonals
        for d in range(2 * self.size - 1):
            row, col = (0, self.size - 1 - d) if d < self.size else (d - self.size + 1, 0)
            current_seq = 0
            while row < self.size and col < self.size:
                if self.primes[self.matrix[row][col]]:
                    current_seq += 1
                    max_seq = max(max_seq, current_seq)
                else:
                    current_seq = 0
                row += 1
                col += 1

        # Check diagonals
        for d in range(2 * self.size - 1):
            row, col = (0, d) if d < self.size else (d - self.size + 1, self.size - 1)
            current_seq = 0
            while row < self.size and col >= 0:
                if self.primes[self.matrix[row][col]]:
                    current_seq += 1
                    max_seq = max(max_seq, current_seq)
                else:
                    current_seq = 0
                row += 1
                col -= 1

        return max_seq


def save_result(n, max_diag, filename="ulam_results.csv"):
    if os.path.exists(filename):
        df = pd.read_csv(filename)
    else:
        df = pd.DataFrame(columns=["n", "max_diagonal"])

    new_entry = pd.DataFrame([{"n": n, "max_diagonal": max_diag}])
    df = pd.concat([df, new_entry], ignore_index=True)
    df.to_csv(filename, index=False)


def update_notebook(filename="ulam_results.ipynb"):
    if os.path.exists("ulam_results.csv"):
        df = pd.read_csv("ulam_results.csv")
    else:
        df = pd.DataFrame(columns=["n", "max_diagonal"])

    df = df.sort_values("n")

    nb = nbf.v4.new_notebook()
    nb["cells"].append(nbf.v4.new_markdown_cell("# Max Diagonal Function"))

    result_text = "## Results:\n"
    for _, row in df.iterrows():
        result_text += f"- For n = {int(row['n'])}, longest diagonal sequence of primes = {int(row['max_diagonal'])}.\n"
    nb["cells"].append(nbf.v4.new_markdown_cell(result_text))

    # Generate a graph
    if not df.empty:
        plt.figure(figsize=(8, 6))
        plt.scatter(df["n"], df["max_diagonal"], color="blue")
        plt.plot(df["n"], df["max_diagonal"], color="red", linestyle="-", marker="o", label="Trend Line")
        plt.xlabel("Matrix Dimension (n)")
        plt.ylabel("Max Diagonal Sequence Length")
        plt.title("Ulam Spiral: Max Diagonal Prime Sequence")
        plt.grid()
        plt.savefig("ulam_plot.png")
        plt.close()
        nb["cells"].append(nbf.v4.new_markdown_cell("## Graph"))
        nb["cells"].append(nbf.v4.new_code_cell('from IPython.display import display\nfrom PIL import Image\ndisplay(Image.open("ulam_plot.png"))'))

    with open(filename, "w") as f:
        nbf.write(nb, f)


def process_n_values(n_values):
    for n in n_values:
        spiral = Ulam(n)
        max_seq = spiral.max_diagonal_sequence()
        print(f"Computed max diagonal sequence for n={n}: {max_seq}")

        save_result(n, max_seq)
        update_notebook()

        print("Updated Jupyter Notebook: 'ulam_results.ipynb'")

if __name__ == "__main__":
    n_values = [n for n in range(50000, 50001)]
    process_n_values(n_values)
