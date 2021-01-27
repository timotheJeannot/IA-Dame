import subprocess;
import time;
import numpy as np
from scipy.stats import multivariate_normal

print("Quel est la taille d'un vecteur ?")
lectTV = input()
TV = int(lectTV)

print("Combien de vecteur faut il générer ?")
lectnbV = input()
nbV = int(lectnbV)

'''
print("Choisissez combien de matchs un vecteur joue")
entree = input()
n = int(entree)
maintenant chaque vecteur joue contre tous les autres vecteurs deux fois
avec un système d'elo
'''

'''''
print("Choisissez combien il y a d'itérations pour l'algorithime")
nbIterR = input()
nbIter = int(nbIterR) # nombre d'itérations pour l'algo de l'entropie croisé, normalement , il faut attendre vers une convergence d'un optimum
'''

print("Choisissez le port de départ")
p = input()
po = int(p)


#paramètres des loies normal pour la première itération
moy = 200#200
var = 4000#49 # rappel : variance = écart-type au carré

#valeurs initial pour les coefficents de l'heuristique de l'ia de reference
iaR = []
v1 = 200
v2 = 1

moyenne = []
variance = [] # à remplacer par la matrice de covariance
coVarMa = []
for i in range(0,TV):
    moyenne.append(moy)
    variance.append(var)
    iaR.append(10)
    ligneCoVar = [0 for i in range(TV)]
    ligneCoVar[i]= var # peut être demandé à l'utilisateur la variance pour chaque variable pour l'itération initial
    coVarMa.append(ligneCoVar)

print("coVarmMa = ")
print(coVarMa)

'''
for i in range (TV):
    #y = multivariate_normal.rvs(mean=2.5, cov=0.5)
    y = multivariate_normal.rvs(moyenne,coVarMa)
    print(y)
print(multivariate_normal.rvs([100,10],coVarMa))
print(multivariate_normal.rvs([100,10],coVarMa))
print(multivariate_normal.rvs([100,10],coVarMa))
print(multivariate_normal.rvs([100,10],coVarMa))
'''

#debut de l'entropie croisé
resultat = []
test = True # test du cas d'arrêt
while test :
#for i in range(0,nbIter) :
    vecteurs = []
    elo = []    # chaque élément contient 3 valeurs : le elo , le coefficient de dévelopement, nombre de matchs effectué 
                # voir https://fr.wikipedia.org/wiki/Classement_Elo#Mode_de_calcul
    strVecteurs = [] # liste permettant de lancer les processus associès à chaque vecteur
    print("-------------------------------------------------------")
    print("i = "+str(i))
    #print("v1 = "+str(v1)) # faire une liste si possible plutot
    #print("v2 = "+str(v2))
    for j in range(0,TV):
        print("iaR["+str(j)+"] = "+str(iaR[j]))

    for j in range(0,nbV):
        # génération d'un vecteur
        print("j = "+str(j))
        vj = [] 
        #strVj = ""
        #strIAR = ["./clientIA_V1","127.0.0.1","dummy value(port)","reference"]
        strIAE = ["./clientIA_V1","127.0.0.1","dummy value(port)","IA_"+str(j)]
        '''
        for k in range(0,TV):
            x = np.random.normal(moyenne[k],variance[k],1)
            vj.append(x[0])
            #strVj += str(x[0])+" "
            #strIAR.append(str(iaR[k]))
            strIAE.append(str(x[0]))
        '''
        vj = multivariate_normal.rvs(moyenne,coVarMa) # https://docs.scipy.org/doc/scipy/reference/generated/scipy.stats.multivariate_normal.html
        for k in range(0,TV):
            strIAE.append(str(vj[k]))

        '''
        vj.append(1000) #elo initial du vecteur (https://www.chess-and-strategy.com/2014/09/le-classement-elo-aux-echecs.html)
                        # on considère que le vecteur est débutant
        vj.append(40) # coefficient k (https://fr.wikipedia.org/wiki/Classement_Elo#Mode_de_calcul)
                      # cette valeur est surement à modifier, un vecteur ne fera pas beaucoup de matchs si il n'y a pas beaucoups
                      #de vecteurs générés. Un joueur d'échec lui va faire un grand nombre de matchs. 
                      # Pour simplifier on a quand même pris le même mode de calcul que décrit dans la page wikipédia
        vj.append(0) # nombre de matchs pour modifier le coefficient k si besoin
        '''
        vj = np.concatenate((vj,np.array([1000,40,0,0])))

        #elo.append([100,40,0])
        strVecteurs.append(strIAE)
        print("vj = ")
        print(vj)
        #vj.append(strIAE)
        vecteurs.append(vj)
    
    for j in range (0,nbV) :
        for k in range (0,nbV) :
            if j != k : # on ne fait pas s'affronter le vecteur contre lui même

                po = po+1
                port = str(po)
                #strIAR[2] = port
                #strIAE[2] = port

                #vecteurs[j][TV+3][2] = port
                #vecteurs[k][TV+3][2] = port
                strVecteurs[j][2] = port
                strVecteurs[k][2] = port

                serveur = subprocess.Popen(["./serveur", port], stdout=subprocess.PIPE,stderr = subprocess.PIPE )
                time.sleep(0.1)
                #client1 = subprocess.Popen(vecteurs[j][TV+3],stdout=subprocess.DEVNULL)
                client1 = subprocess.Popen(strVecteurs[j],stdout=subprocess.DEVNULL)
                time.sleep(0.1) # (suffisant ?) pour s'assurer que le client 1 se connecte en premier au serveur
                                # comme cela chaque vecteur joue contre tous les autres vecteurs, en jouant une fois noir et une fois blanc
                #client2 = subprocess.Popen(vecteurs[k][TV+3],stdout=subprocess.DEVNULL)
                client1 = subprocess.Popen(strVecteurs[k],stdout=subprocess.DEVNULL)

                sortie = serveur.communicate()[0]
                readSortie = str(sortie)
                #cas du match nul : 
                resultatJ = 0.5
                resultatK = 0.5
                # on suppose que le serveur ne renvoie qu'une ligne indiquant qui a gagné
                if "IA_"+str(j) in readSortie :  #victoire de j
                    #nbVictoires += 1
                    resultatJ = 1
                    resultatK = 0
                    vecteurs[j][TV+3] += 1 
               
                if "IA_"+str(k) in readSortie : # pas opti (on parcours deux fois readSortie pour voir qui a gagné)
                    #blabla
                    resultatJ = 0
                    resultatK = 1
                    vecteurs[k][TV+3] += 1 
                

                print("fin d'un match j = "+str(j)+"  k = "+str(k)+ " resultatJ = "+str(resultatJ)+" resultatK = "+str(resultatK)+" nbVicJ = "+ str(vecteurs[j][TV+3])+ " nbVicK = "+str(vecteurs[k][TV+3]) )
                D = vecteurs[j][TV] - vecteurs[k][TV]
                #D = elo[j][0] - elo[k][0]
                #modification du elo de j :
                pD = 1/(1+10**(-D/400))
                vecteurs[j][TV] = vecteurs[j][TV] + vecteurs[j][TV+1]*(resultatJ-pD)
                #elo[j][0] = elo[j][0] + elo[j][1]*(resultatJ-pD)

                #modification du elo de k :
                D = -D
                pD = 1/(1+10**(-D/400))
                vecteurs[k][TV] = vecteurs[k][TV] + vecteurs[k][TV+1]*(resultatK-pD)
                #elo[k][0] = elo[k][0] + elo[k][1]*(resultatK-pD)


                #incrémentation du nombre de match
                vecteurs[j][TV+2] += 1
                vecteurs[k][TV+2] += 1
                #elo[j][2] += 1
                #elo[k][2] += 1

                #modification du coefficiement de développement k du systéme d'elo si besoin
                #ici il faut le  changer , on s'est inspiré des joueurs d'échecs,
                #mais un vecteur va probablement ne pas faire beaucoup de matchs
                # si il y a n vecteurs, il y a (n-1)**2 matchs dans une itération (une ia ne s'affronte pas contre elle même)
                #un vecteur joue alors 2n-2 matchs. Voir quel valeur mettre pour le 30 

                
                if vecteurs[j][TV] < 2400 :
                    vecteurs[j][TV+1] = 20
                else :
                    vecteurs[j][TV+1] = 10
                if vecteurs[j][TV+2] < 30 :
                    vecteurs[j][TV+1] = 40

                if vecteurs[k][TV] < 2400 :
                    vecteurs[k][TV+1] = 20
                else :
                    vecteurs[k][TV+1] = 10
                if vecteurs[k][TV+2] < 30 :
                    vecteurs[k][TV+1] = 40
                '''
                if elo[j][0] < 2400 :
                    elo[j][1] = 20
                else :
                    elo[j][1] = 10
                if elo[j][2] < 30 :
                    elo[j][1] = 40

                if elo[k][0] < 2400 :
                    elo[k][1] = 20
                else :
                    elo[k][1] = 10
                if elo[k][2] < 30 :
                    elo[k][1] = 40
                '''


    vecteurs.sort(key = lambda x:x[TV], reverse=True)
    #print(vecteurs)
    # on enlève ce qui a permis de calculer le classement
    for j in range (0,nbV):
        #vecteurs[j] = np.delete(vecteurs[j],np.s_[TV::TV+3],0)
        eloV = nbVic = vecteurs[j][TV]
        vecteurs[j] = np.delete(vecteurs[j],TV,0)
        vecteurs[j] = np.delete(vecteurs[j],TV,0)
        vecteurs[j] = np.delete(vecteurs[j],TV,0)
        nbVic = vecteurs[j][TV] = vecteurs[j][TV]
        vecteurs[j] = np.delete(vecteurs[j],TV,0)
        print(vecteurs[j])
        print(" nombre de victoires = "+str(nbVic) + " ; elo = "+str(eloV))

    # sélections des vecteurs pour le calcul de la nouvelle moyenne et de la nouvelle variance
    nbToKeep = int(nbV/3)+1
    vecteursKept = vecteurs[0:nbToKeep]

    '''
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
    '''
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
            #on met à jour l'ia de référence
            iaR[j] = vecteurs[0][j]

        #calcul des nouvelles variances
        '''
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
        '''

        #calcul de la matrice de covariance
        coVarMa = np.cov(np.array(vecteursKept).T) #https://numpy.org/doc/stable/reference/generated/numpy.cov.html
        print("vecteur moyenne")
        print(moyenne)
        print("coVarMa")
        print(coVarMa)

        # cas d'arrêt de l'algorithme (il vaut mieux faire une boucle while et quitter direct quand on a une valeur sup à 1, mais bon ce qui ce qui coute le plus dans le processus)
        test = False
        for j in range(0,TV):
            if coVarMa[j][j] > 1 :
                test = True

    
    resultat = vecteursKept

f= open("resultatEntropie.txt","w")
size = len(resultat)
for i in range(0,size) :
    f.write(" ||| ".join(str(resultat[i]))+"\n")
f.close()

#problèmes : 
             #1 -comment savoir quand l'optimum est atteint ? On ne converge pas 
             # -améliorer le choix du port
             #2 -parallélisation
             # -on peut enlever le sleep?
             # -rendre les variables dépendantes : voir les vecteurs gaussiens, matrices de covariance
             #3 -gérer l'ordre des joueurs
             #4 -faire un deuxième serveur qui renvoie juste le joueur gagnant (le premier affichant les états des plateaux)
             # -tous les matchs d'un même vecteur vont être pareil face à l'ia de référence. solutions potentiels:
                # on choisi l'ia de référence en suivant une loi normal avec une moyenne =  meilleur coef de la série précédentes . On prend une variance faible genre 1 ou 2
                # on choisi un premier coup aléatoirement
                # on ne fait que 1 match pour chaque vecteu

    
             
             


    

        


