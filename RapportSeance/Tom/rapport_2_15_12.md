# Rapport de séance 2 du 15/12
Lors de cette séance j'ai testé les composants électroniques liés au boitier, essayer de comprendre
pourquoi l'IA ne fonctionnait pas et obtenu des précisions sur le matériel lié au dirigeable.
Voici le lien vers les codes des différents tests : [link](../../Boitiers/README.md)

## Travail de la séance

L'objectif de la séance était de vérifier que les composants marchaient, et de trouver le code
permettant de les faire fonctionner dans le cadre du projet.

### Module Doppler

Le premier module que j'ai testé est celui permettant la détection des personnes et véhicules
grâce à l'envoie d'une onde. Ce module possède 3 fils, 2 pour l'alimentation et 1 qui s'active
quand du mouvement est détecté. Après deux tests avec un simple programme lisant si le câble était
à LOW ou HIGH, puis un programme lisant le voltage du signal, je me suis rendu compte que le module
envoyait un signal très faible. M.Masson est intervenu en me disant que le module nécéssitait un
amplificateur pour être opérationnel. J'ai donc utilisé un autre module qui est déja équipé d'un
amplificateur opérationnel et qui possède la même configuration de câble que l'autre module.
Cette fois-ci un code d'exemple, a parfaitement marché, il ne restera plus que la calibration
de distance.

### Module Photodiode

Le second module que j'ai testé est celui permettant de capter la luminosité ambiante. Il est utilisé
pour que les lampadaires ne s'allument pas si la luminosité ambiante est deja assez élevée. Il est 
composé de 4 pins, 2 d'alimentations, 2 de données (1 qui renvoie une signal HIGH si la luminosité
dépasse un seuil controllable par un potentiomètre et 1 qui renvoie un signal analogique proportionnel
à la luminosité. Après un court programme exemple trouvé, et un test en mettant ma main sur le capteur
ce-dernier répondait bien au variation de lumière. Il ne reste plus qu'à trouver un formule pour 
convertir le signal analogique en lumens, l'unité de mesure de la lumière.

### Camera Thermique

Le troisième module que j'ai testé est celui permettant de détecter les personnes et les véhicules
par la chaleur. Ce module renvoie une matrice de température de 64 "pixels", il faut les analyser
et le mettre en corrélation pour détecter un chargement. Ce module est fonctionnel, il faut trouver
comment mettre en place la corrélation.

### Module Timer

Le dernier module que j'ai testé est celui permettant de garder en mémoire l'heure et la date courante.
Il est utilisé en complément du module de photodiode, en permettant l'activation ou la désactivation du
scanner par photodiode à des heures précises (par exemple pour des événements ou des travaux). Apres avoir
trouvé et testé le code d'exemple j'ai reussi à mettre le module à une certaine heure et la lire. En revanche
je n'ai pas reussi à conserver l'heure des que l'Arduino n'était plus alimenté. Cela est probalement du à
un soucis de pile que je devrait résoudre. La communication par le protocole I2C n'a pas été compliqué grâce
à la documention sur Internet.

### Correction IA

Lors de cette séance un des objectif était également de finir la reconnaissance de personnes et de véhicules 
par IA. En effet lors de la dernier séance par manque de temps cela avait était impossible. Après avoir
téléverser le code, l'écran reste indéfiniment sur le chargement. Afin de comprendre les problèmes une led verte
 et une led rouge ont été ajouter elle était sensé s'allumer en fonction de l'avancement et des erreurs.
 La communication Serial n'était pas disponible car j'effectuais les tests sur une autre Arduino en même temps
 et l'ordinateur ne pouvait supporter la charge de courant.
 Les résultasts ont montré que le chargement du modèle de prédiction s'effectuer correctement ainsi que 
 la détection mais que l'affichage rencontré un problème. Il devra être corriger.

### Dirigeable

Lors de la séance M.Masson m'a également montré, le dirigrable utilisé par les années précédentes afin que 
je vois comment je dois m'organiser. Le dirigeable est composé du ballon, et d'une nacelle équipée en
matériels de réception d'ordre et d'une télécommande. Tout cela sera étudié dans les derniers séances. Le dirigeable
 est considéré comme un apport esthétique, la plus value étant sur l'IA.

## Travail à faire

Pour la prochaine séance le travail à faire à la maison est :
- Corriger et terminer l'IA
- Corriger le Timer
- Trouver la formule pour la photodiode
- Calibrer le Doppler 
- Mettre en place la corrélation de la camera thermique