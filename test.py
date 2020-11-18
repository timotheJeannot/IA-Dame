import subprocess;

serveur = subprocess.run(["./serveur", "6767"], capture_output=True);
client1 = subprocess.run(["./client", "127.0.0.1 6767 test"], capture_output=True);
client2 = subprocess.run(["./client", "127.0.0.1 6767 test2"], capture_output=True);
print(serveur.stdout);

