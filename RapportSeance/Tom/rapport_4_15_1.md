# Rapport de séance 4 du 15/01
Lors de cette séance, je suis passé à l'oral sur mon projet, j'ai également régler le problème
du capteur Doppler afin qu'il détecte correctement les mouvements. J'ai corrigé le problème 
d'alimentaion du module Timer. Pour finir j'ai ajouté le module de détection de la lumoière.

## Plaquette 3D
J'ai déssiné et imprimer une pièce en 3D qui permet de fixer les capteurs pour qu'ils ne bougent pas
et ne soit pas parasiter.

## Présentation
J'ai passè la première heure de la séance à reconstruire l'entièreté du système composé de
la reconnaissance par IA, du capteur thermique, du module Bluetooth et du Timer.
Puis j'ai relancé la liaison Bluetooth avec l'application.
Enfin j'ai présenté l'avancement de mon projet avec les différents capteurs, qui sont montés
sur une impression 3D que j'ai réalisé et quip permet de stabiliser les capteurs de mouvements
et de chaleur.

## Capteur Doppler
Monter le capteur Doppler sur la plaquette 3D, à parmis de le stabiliser, ce qui permet de ne
plus avoir de mouvements parasite. Le potentiometre permettant de gérer la distance a été
tourné vers le plus bas, puis remonter doucement afin d'atteindre une distance de détection
convenable. Il a ensuite été relié à l'Arduino afin de pouvoir envoyer une message Bluetooth
au portable.

## Camera Thermique
La camera thermique a été montée aussi sur la plaquette afin de stabiliser sa détection.

## Module Timer
Après mesure de tension, je me suis rendu compte que la pile du Timer n'envoyait qu'une tension
de 1,6V ce qui est trop peu pour que le module de sauvegarde de l'heure marche. Je l'ai donc
remplacé par une autre pile de 3V, ce qui a permis de le faire fonctionner correctement.
Il a pu retenir l'heure, même si l'Arduino était débranchée.

## Module Lumière
J'ai branché le module de lumière afin de détecter le luminosité ambiante pour déclencher où 
non les lampadaires.

## Dirigeable
Enfin, Monsieur Masson, m'a proposé de re-commander un dirigeable au près d'une entreprise espagnol.