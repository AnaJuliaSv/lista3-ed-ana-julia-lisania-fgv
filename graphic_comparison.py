import csv
import matplotlib.pyplot as plt

# Lê o csv gerado pelo benchmark.cpp
sizes = []
insertion_times = []
merge_times = []

with open("benchmark.csv", newline="") as f:
    reader = csv.DictReader(f)
    for row in reader:
        sizes.append(int(row["tamanho"]))
        insertion_times.append(float(row["insertion_sort_ms"]))
        merge_times.append(float(row["merge_sort_ms"]))

# Gera dois gráficos de linhas
fig, axes = plt.subplots(1, 2, figsize=(14, 5))

# Escala linear
axes[0].plot(sizes, insertion_times, marker="o", label="Insertion Sort", color="tomato")
axes[0].plot(sizes, merge_times, marker="s", label="Merge Sort", color="steelblue")
axes[0].set_title("Comparação de tempo — escala linear")
axes[0].set_xlabel("Número de jogadores")
axes[0].set_ylabel("Tempo (ms)")
axes[0].legend()
axes[0].grid(True)

# Escala log-log: filtra zeros para evitar erro
sizes_log, ins_log, merge_log = [], [], []
for s, ins, mg in zip(sizes, insertion_times, merge_times):
    if ins > 0 and mg > 0:
        sizes_log.append(s)
        ins_log.append(ins)
        merge_log.append(mg)

if sizes_log:
    axes[1].plot(sizes_log, ins_log, marker="o", label="Insertion Sort", color="tomato")
    axes[1].plot(sizes_log, merge_log, marker="s", label="Merge Sort", color="steelblue")
    axes[1].set_title("Comparação de tempo — escala log-log")
    axes[1].set_xlabel("Número de jogadores")
    axes[1].set_ylabel("Tempo (ms)")
    axes[1].set_xscale("log")
    axes[1].set_yscale("log")
    axes[1].legend()
    axes[1].grid(True, which="major", linestyle="-", alpha=0.5)
else:
    axes[1].text(0.5, 0.5, "Tempos muito pequenos\npara escala log-log",
                 ha="center", va="center", transform=axes[1].transAxes)
    axes[1].set_title("Escala log-log indisponível")

plt.tight_layout()
plt.savefig("benchmark.png", dpi=150)
plt.show()
print("Gráfico salvo em benchmark.png")