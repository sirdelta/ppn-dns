
# Extension de la Résolution de Noms pour le HPC

Fonctionnement
---------------------------------

Nom provisoire de la bibliothèque : P2I - _Process Identification Interface_

Permet aux programmes HPC de faciliter l'identification des processus les uns par rapport au autre.
L'identification est assurée par un mécanisme de résolution de noms, qui utilise une version simplifiée et adaptée du protocole DNS.
La mise en place d'une DHT (_Distributed Hash-Table_) permet le partage d'informations d'identification entre processus.

Pour le moment, l'arborescence du projet est la suivante :

 * __build__ : fichiers binaires/exécutables ;
 * __build/bin__ : exécutables à générer ;
 * __build/lib__ : bibliothèque à générer ;
 * __dep__ : bibliothèques extérieurs, plugins et dépendances utilisés dans notre programme ;
 * __src__ : fichiers sources du programme ;
 * __include__ : fichier d'entêtes associées au notre programme, entête de la bibliothèque à générer ;
 * __exe__ : fichiers sources des exécutables qui utiliseront la bibliothèque  à générer ;
 * __tests__ : fichiers sources des tests de validation des fonctions.

Le fichier __.gitignore__ contient les éléments qui ne seront pas ajouter à l'arborescence finale.

Le fichier __run.sh__ sera utilisé pour faciliter la compilation automatique et l'exécution des différents programmes.

Les fichiers __Makefile__ et __README.md__ seront complétés et améliorés au fur et à mesure.

Les dossiers et éléments cités ci-dessus n'apparaissant pas dans l'arborescence sont soit vides, soit non-exploités pour le moment.
Pour plus d'information concernant les implémentations antérieurs du projet, consultez [le drive du projet](https://drive.google.com/drive/folders/1eYObzYu2bYIsx-OR9TyHlNd9kDHZ15J7?usp=sharing).

Ressources et liens
---------------------------------
* [Sujet du projet](https://datafront.maqao.exascale-computing.eu/public_html/CHPS/projets.html#extension-de-la-r%C3%A9solution-de-noms-pour-le-hpc)
* [Suivi du projet - Hedgedoc du prof](https://france.paratools.com/hedgedoc/s/Z8mPoPvTL)
* [Drive du projet : Organisation et documentation](https://drive.google.com/drive/folders/1eYObzYu2bYIsx-OR9TyHlNd9kDHZ15J7?usp=sharing)

Tâches à faire
---------------------------------

* Implémentation des fonctions de compression et décompression des messages échangés. [EN COURS]
* Implémentation des fonctions relatives aux communications TCP/IP. [EN COURS]
* Implémentation du Client/Serveur unifié. [EN COURS]
* Mise à jour de la table de hachage. [EN COURS]
* Réalisation des tests de validation des fonctions et routines.
* ...
