import subprocess
import time

hilos_a_probar = [1, 2, 4, 8, 16, 32]
repeticiones = 5

print("Hilos, Corrida 1, Corrida 2, Corrida 3, Corrida 4, Corrida 5, Promedio")
for h in hilos_a_probar:
    tiempos = []
    for r in range(repeticiones):
        inicio = time.time()
        subprocess.run(["./practica2", str(h)], stdout=subprocess.DEVNULL)
        fin = time.time()
        tiempos.append(fin - inicio)
    
    promedio = sum(tiempos) / repeticiones
    print(f"{h}, " + ", ".join([f"{t:.2f}" for t in tiempos]) + f", {promedio:.2f}")
