
Ressouces et liens
---------------------------------
* [Sujet du projet](https://datafront.maqao.exascale-computing.eu/public_html/CHPS/projets.html#extension-de-la-r%C3%A9solution-de-noms-pour-le-hpc)
* [Suivi du projet - Hedgedoc du prof](https://france.paratools.com/hedgedoc/s/Z8mPoPvTL)
* [Github du projet](https://github.com/sirdelta/ppn-dns)
* [Organisation et documentation](https://drive.google.com/drive/folders/1eYObzYu2bYIsx-OR9TyHlNd9kDHZ15J7?usp=sharing)  

Programme
---------------------------------

Pour le moment, l'arorescence du projet est la suivante :

 * build : fichiers binaires/exécutables
 * build/lib : c'est dans ce répertoire que seront stockées les bibliothèques générées

 * dep : bibliothèques extérieurs, plugins et dépendances utilisés dans notre programme

 * src : fichiers sources et entêtes associées à notre programme
 * inc :  c'est dans ce répertoire que seront rangées les entêtes UNIQUEMENT destinées à appeler les bibliothèques générées

 * exe : fichiers sources des exécutables qui utiliseront les bibliothèques générées
 * tests : fichiers sources des tests de validation de nos fonctions


Le fichier __.gitignore__ contient les éléments qui ne seront pas _pusher_ sur le git du projet.

Le fichier __run.sh__ sera utilisé pour faciliter la compilation automatique et l'exécution des différents programmes.

Les fichiers __Makefile__ et __README.md__ seront complétés au fur et à mesure.
