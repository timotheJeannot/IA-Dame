import subprocess;
import time;

print("Choisissez combien de fois vous souhaitez éxécutez les programmes")
entree = input()
n = int(entree)
resultat = ""
print("Choisissez le port de départ")
p = input()
po = int(p)

for i in range (0,n) : 
	port = str(po+i)
	serveur = subprocess.Popen(["./serveur", port], stdout=subprocess.PIPE)
	time.sleep(1)
	client1 = subprocess.Popen(["./client", "127.0.0.1", port,  "test"], stdout=subprocess.DEVNULL)
	client2 = subprocess.Popen(["./client", "127.0.0.1", port, "test2"], stdout=subprocess.DEVNULL)
	sortie = serveur.communicate()[0]
	resultat += str(sortie) + " \n"

#print(resultat)
f = open("resultat.txt", "w")
f.write(resultat)
f.close()
