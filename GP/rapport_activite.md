# Rapport d'activité - Projet Compilation GRP-13

_Janvier 2026_

---

## 1. Vue d'ensemble du projet

Le projet de création d'un compilateur a progressé de manière collaborative avec une répartition des tâches entre les membres de l'équipe. L'ensemble du projet a été structuré autour de deux axes principaux : la grammaire et les fonctions sémantiques.

## 2. Organisation du travail

Le travail a été effectué selon deux modes complémentaires :

**Travail collectif :** Les décisions majeures concernant la grammaire et les fonctions sémantiques ont été prises ensemble lors de réunions d'équipe, permettant une vision cohérente du projet.

**Travail individuel :** Chaque membre de l'équipe a ensuite pris en charge des tâches spécifiques en dehors des réunions pour assurer l'avancement du projet.

## 3. Répartition des tâches individuelles

Les tâches suivantes ont été distribuées entre les quatre membres de l'équipe :

| Guillaume                                                                                     | Kévin                                                                                                                                                | Thomas                                                                                                                                                          | Quentin                                                   |
| --------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------- |
| • Affichage de l'AST en graphviz<br>• GP: Compte rendu réussi<br>• Ajout de fonctions de test | • Première affichage de l'AST en cmd pour tester et debugger<br>• Mise à jour de l'affichage avec graphviz pour afficher les champs quand nécessaire | • Lexer : Implémentation du lexer puis le relier avec le parseur de Bison<br>• Implémenter un wrapper pour encapsuler l'AST (C++) car la grammaire compile en C | • Gestion des erreurs sémantiques<br>• Création des règles de priorités<br>• Modification de la grammaire pour éviter les boucles de dérivation<br>• Débogage de tout ce qui a pas marché<br>|
## 4. Difficultés rencontrées

Au cours du développement, l'équipe a identifié deux difficultés principales :

**Grammaire difficile à débugger :** La complexité de la grammaire a rendu le processus de débogage particulièrement ardu, nécessitant une attention minutieuse et des outils de visualisation appropriés.

**Compatibilité entre code C++ et code C généré par Bison :** L'intégration entre le code C++ développé pour le projet et le code C généré automatiquement par Bison a posé des défis de compatibilité importants, notamment au niveau de l'encapsulation et de la gestion des interfaces.

## 5. Grammaire du langage

La grammaire (Bison) couvre les concepts suivants : classes (avec `extends`), constructeur, méthodes (typées et `void`), une classe `Main` avec la signature Java-like, instructions (déclarations/affectations, `if`/`else`, `for`, `return`, blocs), et des expressions avec appels de méthodes, accès/affectation de champs et opérateurs unaires/binaires avec précédences.

Extrait synthétique (EBNF simplifié) issu de `parser/grammar.y` :

```bnf
file ::= class_star class_Main


bracket_open ::= BRACKET_OPEN
bracket_close ::= BRACKET_CLOSE

curlbracket_open ::= CURLBRACKET_OPEN
curlbracket_close ::= CURLBRACKET_CLOSE

class_star ::= ε | class_star class

class ::= CLASS IDENT curlbracket_open decl_star curlbracket_close | CLASS IDENT EXTENDS IDENT curlbracket_open decl_star curlbracket_close


decl_star ::= ε | decl_star decl
decl ::= type IDENT semi_colon | constructor | method
constructor ::= IDENT bracket_open params_opt bracket_close curlbracket_open stmt_star curlbracket_close


method ::= type IDENT bracket_open params_opt bracket_close curlbracket_open stmt_star curlbracket_close | VOID IDENT bracket_open params_opt bracket_close curlbracket_open stmt_star curlbracket_close
params_opt: ε | params

params ::= type IDENT | params COMA type IDENT

type ::= BOOLEAN | INT | IDENT | STRING_C

class_Main ::= CLASS MAIN curlbracket_open PUBLIC STATIC VOID MAIN_C bracket_open STRING_C IDENT SQUBRACKET_OPEN SQUBRACKET_CLOSE bracket_close

expr ::= INTEGER | STRING 
| TRUE | FALSE
| THIS
| NULL_TOKEN
| bracket_open expr bracket_close
| IDENT 
| IDENT postfix_expr
| THIS postfix_expr
| NEW IDENT bracket_open lexpr_opt bracket_close
| NEW STRING_C bracket_open lexpr_opt bracket_close
| NOT expr
| MINUS expr NEGATIVE
| bracket_open type bracket_close expr CAST

expr_deg1 ::= expr_deg1 OR expr_sans_binop
| expr_deg2 OR expr_deg1
| expr_deg2

  
expr_deg2 ::= expr_deg3 AND expr_deg2
| expr_deg3
  
expr_deg3 ::= expr_deg3 EQUALS expr_sans_binop
| expr_deg3 DIFFERENT expr_sans_binop
| expr_deg4 EQUALS expr_deg3
| expr_deg4 DIFFERENT expr_deg3
| expr_deg4
  
expr_deg4 ::= expr_deg4 SMALLER expr_sans_binop
| expr_deg4 SMALLER_OR_EQUAL expr_sans_binop
| expr_deg4 BIGGER expr_sans_binop
| expr_deg4 BIGGER_OR_EQUAL expr_sans_binop
| expr_deg5 SMALLER expr_deg4
| expr_deg5 SMALLER_OR_EQUAL expr_deg4
| expr_deg5 BIGGER expr_deg4
| expr_deg5 BIGGER_OR_EQUAL expr_deg4
| expr_deg5

expr_deg5 ::= expr_deg5 PLUS expr_sans_binop
| expr_deg5 MINUS expr_sans_binop
| expr_deg6 PLUS expr_deg5
| expr_deg6 MINUS expr_deg5
| expr_deg6
  
expr_deg6 ::= expr_deg6 TIMES expr_sans_binop
| expr_deg6 DIVIDE expr_sans_binop
| expr_deg6 REMAIN expr_sans_binop
| expr_sans_binop
  

expr_sans_binop ::= INTEGER
| STRING
| TRUE
| FALSE
| THIS
| NULL_TOKEN
| bracket_open expr bracket_close
| IDENT postfix_expr_sans_binop
| THIS postfix_expr_sans_binop
| NEW IDENT bracket_open lexpr_opt bracket_close
| NEW STRING_C bracket_open lexpr_opt bracket_close
| NOT expr_sans_binop
| MINUS expr_sans_binop NEGATIVE
| bracket_open type bracket_close expr_sans_binop CAST


postfix_expr ::= ε
| SET expr
| bracket_open lexpr_opt bracket_close
| POINT IDENT
| POINT IDENT SET expr
| POINT IDENT bracket_open lexpr_opt bracket_close
| INSTANCE_OF type

postfix_expr_sans_binop ::= ε
| SET expr_sans_binop
| bracket_open lexpr_opt bracket_close
| POINT IDENT
| POINT IDENT SET expr_sans_binop
| POINT IDENT bracket_open lexpr_opt bracket_close
| INSTANCE_OF type


lexpr_opt ::= ε | lexpr

lexpr ::= expr | lexpr COMA expr

stmt_star ::= ε | stmt_star stmt

stmt ::= semi_colon
| expr semi_colon
  | type IDENT semi_colon
  | type IDENT SET expr semi_colon
  | if_cond
  | for_loop
  | curlbracket_open stmt_star curlbracket_close
  | RETURN semi_colon
  | RETURN expr semi_colon
  | method

if_cond ::= IF bracket_open expr bracket_close stmt LOWER_THAN_ELSE
| IF bracket_open expr bracket_close stmt ELSE stmt


for_loop: FOR bracket_open expr_opt semi_colon expr_opt semi_colon expr_opt bracket_close stmt

semi_colon: SEMI_COLON

expr_opt ::= ε | expr
```

Précédences (de la plus faible à la plus forte) : `=` (droite), `||`, `&&`, `== !=`, `< <= > >= instanceof`, `+ -`, `* / %`, puis unaires `-` et `!`, et le `cast`.

La grammaire intègre des règles de récupération d'erreurs (ex. parenthèses/accolades manquantes) et signale des messages explicites.

## 6. Structure de l'arbre abstrait (AST)

L'AST est défini dans `AST/AST_types.h` et construit via les wrappers C dans `AST/AST_wrapper.{h,cpp}`. Chaque nœud `ASTNode` contient `type`, `name`/`int_val`/`str_val` et une liste de `children`.

Catégories principales de nœuds (sélection) :

- Déclarations/classes : `NODE_FILE`, `NODE_CLASS`, `NODE_CLASS_EXTENDS`, `NODE_EXTENDS`, `NODE_MAIN`, `NODE_CONSTRUCTOR`, `NODE_METHOD`, `NODE_METHOD_VOID`.
- Types/identifiants : `NODE_TYPE`, `NODE_IDENTIFIER`, `NODE_PARAM`, `NODE_PARAMETER_LIST`.
- Instructions : `NODE_STMT`, `NODE_STMT_EMPTY`, `NODE_STMT_EXPR`, `NODE_VAR_DECL`, `NODE_VAR_DECL_INIT`, `NODE_RETURN`, `NODE_IF`, `NODE_IF_ELSE`, `NODE_FOR`.
- Expressions scalaires : `NODE_TRUE`, `NODE_FALSE`, `NODE_THIS`, `NODE_NULL`, `NODE_INTEGER`, `NODE_STRING`.
- Accès/appels/affectations : `NODE_FIELD`, `NODE_FIELD_SET`, `NODE_METHOD_CALL`, `NODE_SET`.
- Opérations : `NODE_NOT`, `NODE_NEG`, `NODE_CAST`, `NODE_BINOP` (porte l'opérateur en `name`), `NODE_NEW`, `NODE_INSTANCEOF`.
- Erreur : `NODE_ERROR` (créé par les productions de récupération).

La génération Graphviz (`AST/AST.cpp`) produit des étiquettes lisibles (ex. `VAR_DECL`, `BINOP` avec l'opérateur, valeurs litérales sur le label) et remet certains identifiants comme enfants pour les déclarations/affectations.

## 7. Jeux d'essais

Des tests sont fournis dans `Test/Ok` (programmes valides) et `Test/Erreurs` (déclenchement de la récupération d'erreurs).

- Valides (extraits) :
  - `Test/Ok/Base.jura` — squelette de programme minimal avec `Main`.
  - `Test/Ok/add.jura` — déclarations/affectations et `+` (opérateurs binaires).
  - `Test/Ok/if1.jura` — `if/else`, comparaison `==`, parenthèses imbriquées.
  - `Test/Ok/for.jura` — boucle `for` avec init/cond/incr et expressions arithmétiques.
  - `Test/Ok/Class.jura` — déclaration d'une classe annexe + `Main`.

Exemples courts issus des fichiers :

```java
// Test/Ok/add.jura
class Main{
	public static void main (String test []){
		int a = 1;
		int b = 2;
		int c;
		int c = a + b;
	}
}
```

```java
// Test/Ok/for.jura
class Main{
	public static void main (String test []){
		int a; a = 0; int i;
		for (i = 0; i < 5; i = i + 1) {
			a = a * 1 - 1;
		}
	}
}
```

- Erreurs (extraits) :
  - `Test/Erreurs/Synt1.jura` — mots-clés isolés et `;` manquant dans `main` (récupération d'erreurs active et messages explicites).
  - `Test/Erreurs/Lex1.jura`, `Lex2.jura` — cas lexicaux non conformes (selon le lexer).

## 8. Estimation du temps par étape

Estimation indicative par grandes étapes de cette première partie. Merci de renseigner les durées réelles avant la soutenance.

| Étape                              | Membre(s)                | Estimé (h) | Réel (h) | Commentaires                                                                                                               |
| ---------------------------------- | ------------------------ | ---------: | -------: | -------------------------------------------------------------------------------------------------------------------------- |
| Conception de la grammaire (Bison) | Thomas + Quentin         |          4 |        4 |                                                                                                                            |
| Implémentation du lexer            | Thomas                   |          4 |        5 |                                                                                                                            |
| Construction de l'AST + wrappers   | Thomas, Kévin            |          7 |       14 | Cette partie ne prend en compte que la durée d'implémentation de l'arbre, sa structure ayant déjà été définie au préalable |
| Gestion des erreurs sémantiques    | Quentin                  |          5 |        7 | La documentation sur la gestion des erreurs manque cruellement de particité                                                |
| Intégration parser ↔ AST + erreurs | Quentin + Thomas         |         10 |       15 |                                                                                                                            |
| Visualisation Graphviz (DOT/PNG)   | Guillaume                |          5 |        4 |                                                                                                                            |
| Jeux d'essais (Ok/Erreurs)         | Thomas, Guillaume, Kevin |          4 |        6 |                                                                                                                            |

## 9. Conclusion

Le projet avance de manière structurée grâce à une répartition efficace des tâches et une collaboration étroite entre les membres de l'équipe. Les difficultés identifiées font l'objet d'un travail continu pour les résoudre et permettre la poursuite du développement du compilateur dans les meilleures conditions. Les éléments techniques requis (grammaire, structure AST, jeux d'essais) sont intégrés dans ce rapport.
