import os


exclude_dirs = {
    ".git", "bin", "screen",
    "build"
}


def count_lines(root_dir="."):
    total_lines = 0
    for root, dirs, files in os.walk(root_dir):
        # Rimuovi le cartelle escluse dalla scansione
        dirs[:] = [d for d in dirs if d not in exclude_dirs]

        for file in files:
            filepath = os.path.join(root, file)
            try:
                print(filepath)
                with open(filepath, "r", encoding="utf-8", errors="ignore") as f:
                    lines = sum(1 for _ in f)
                    total_lines += lines
            except Exception as e:
                print(f"Errore leggendo {filepath}: {e}")

    return total_lines


if __name__ == "__main__":
    lines_counted = count_lines()
    print(f"Totale righe codice {lines_counted}")
