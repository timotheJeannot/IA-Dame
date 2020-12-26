import subprocess;
import time;
import numpy as np

print("Quel est la taille d'un vecteur ?")
lectTV = input()
TV = int(lectTV)

print("Combien de vecteur faut il générer ?")
lectnbV = input()
nbV = int(lectnbV)

print("Choisissez combien de matchs un vecteur joue")
entree = input()
n = int(entree)

print("Choisissez combien il y a d'itérations pour l'algorithime")
nbIterR = input()
nbIter = int(nbIterR) # nombre d'itérations pour l'algo de l'entropie croisé, normalement , il faut attendre vers une convergence d'un optimum

print("Choisissez le port de départ")
p = input()
po = int(p)

#paramètres des loies normal pour la première itération
moy = 10#200
var = 4#49 # rappel : variance = écart-type au carré

#valeurs initial pour les coefficents de l'heuristique de l'ia de reference
v1 = 200
v2 = 1

moyenne = []
variance = []
for i in range(0,TV):
    moyenne.append(moy)
    variance.append(var)

#debut de l'entropie croisé
resultat = []
for i in range(0,nbIter) :
    vecteurs = []
    print("-------------------------------------------------------")
    print("i = "+str(i))
    print("v1 = "+str(v1)) # faire une liste si possible plutot
    print("v2 = "+str(v2))

    for j in range(0,nbV):
        # génération d'un vecteur
        print("j = "+str(j))
        vj = [] 
        strVj = ""
        for k in range(0,TV):
            x = np.random.normal(moyenne[k],variance[k],1)
            vj.append(x[0])
            strVj += str(x[0])+" "
        print("vj = ")
        print(vj)
        #strVj = " ".join(str(vj))
        nbVictoires = 0
        for k in range (0,n) :
            po = po+1
            port = str(po)
            serveur = subprocess.Popen(["./serveur", port], stdout=subprocess.PIPE,stderr = subprocess.PIPE )
            time.sleep(1)
            client1 = subprocess.Popen(["./clientIA_V1", "127.0.0.1", port,  "reference" ,str(v1), str(v2)], stdout=subprocess.DEVNULL) # il faut peut être mieux changé la référence au fur et à mesure des itérations de l'entropie croisé
            #client2 = subprocess.Popen(["./clientIA_V1", "127.0.0.1", port, "IA_E",strVj], stdout=subprocess.DEVNULL)
            client2 = subprocess.Popen(["./clientIA_V1", "127.0.0.1", port, "IA_E",str(vj[0]),str(vj[1])], stdout=subprocess.DEVNULL)
            
            sortie = serveur.communicate()[0]
            readSortie = str(sortie)
            if "IA_E" in readSortie :  # on suppose que le serveur ne renvoie qu'une ligne indiquant qui a gagné
                nbVictoires += 1
            print("fin d'un match")

        vj.append(nbVictoires)
        vecteurs.append(vj)

    vecteurs.sort(key = lambda x:x[TV], reverse=True)
    print(vecteurs)

    # sélections des vecteurs pour le calcul de la nouvelle moyenne et de la nouvelle variance
    nbToKeep = int(nbV/3)+1
    vecteursKept = vecteurs[0:nbToKeep]

    size = len(vecteursKept)
    print("size = "+str(size))
    j2 = 0  # il faudrai faire une boucle while ici (plus propre) quand j'ai fais j = j -1 cela n'a pas fonctionné avec le for
            # c'est pour cela que je passe par une seconde variable
    for j in range(0,size):
        if vecteurs[j2][TV] <= (int (n/2)) : #on supprime les vecteurs qui n'ont pas gagnés assez de matchs
            vecteursKept.pop(j2)
            size = size-1
            j2 = j2-1
        j2 = j2 +1

    print("vecteurs kept = ")
    print(vecteursKept)

    size = len(vecteursKept)
    if size > 0 :

        #sélection des nouveaux coefficients pour la nouvelle ia de référence pour la prochaine itération

        #attention ici je suppose que TV =2 , normalement il faut faire une liste pour stocker les vi
        v1 = vecteurs[0][0]
        v2 = vecteurs[0][1]
        # calcul des nouvelles moyennes 
        moyenne = [0 for j in range(0,TV)]
        for j in range(0,TV):
            for k in range(0,size):
                moyenne[j] += vecteursKept[k][j]
            moyenne[j] = moyenne[j]/size

        #calcul des nouvelles variances

        variance = [0 for j in range(0,TV)]

        for j in range(0,TV):
            for k in range(0,size):
                variance[j] += (vecteursKept[k][j] - moyenne[j])**2
            variance[j] = variance[j] / size
            if variance[j] == 0 : # quand il n'y a que un vecteur de sélectionne la variance vaut 0 et il n'y a plus de changements
                variance[j] = moyenne[j]/2
            if variance[j] < 1 :   #je réaugmente un peu la variance, si jamais elle descend en dessous de 1 par hasard,il n'y a plus de changement
                                    #je ne pense pas qu'on puisse considérer que l'optimum soit trouvé comme cela
                variance[j] = 2
            print("moyenne["+str(j)+"] = "+str(moyenne[j]))
            print("variance["+str(j)+"] = "+str(variance[j]))

    
    resultat = vecteursKept

f= open("resultatEntropie.txt","w")
size = len(resultat)
for i in range(0,size) :
    f.write(" ||| ".join(str(resultat[i]))+"\n")
f.close()

#problèmes : -comment savoir quand l'optimum est atteint ? est ce que on est sur qu'on converge actuellement ?
             # -améliorer le choix du port
             # -parallélisation
             # -on peut enlever le sleep? ou le réduire ?
             # -rendre les variables dépendantes : voir les vecteurs gaussiens, matrices de covariance
             # gérer l'ordre des joueurs
             # faire un deuxième serveur qui renvoie juste le joueur gagant (le premier affichant les états des plateaux)
             # tous les matchs d'un même vecteur vont être pareil face à l'ia de référence. solutions potentiels:
                # on choisi l'ia de référence en suivant une loi normal avec une moyenne =  meilleur coef de la série précédentes . On prend une variance faible genre 1 ou 2
                # on choisi un premier coup aléatoirement
                # on ne fait que 1 match pour chaque vecteur
             
             


    

        


