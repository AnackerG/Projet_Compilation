# Rapport d'activité - Projet Compilation GRP-13

*Janvier 2026* 

---

## 1. Vue d'ensemble du projet

Le projet de création d'un compilateur a progressé de manière collaborative avec une répartition des tâches entre les membres de l'équipe. L'ensemble du projet a été structuré autour de deux axes principaux : la grammaire et les fonctions sémantiques.

## 2. Organisation du travail

Le travail a été effectué selon deux modes complémentaires :

**Travail collectif :** Les décisions majeures concernant la grammaire et les fonctions sémantiques ont été prises ensemble lors de réunions d'équipe, permettant une vision cohérente du projet.

**Travail individuel :** Chaque membre de l'équipe a ensuite pris en charge des tâches spécifiques en dehors des réunions pour assurer l'avancement du projet.

## 3. Répartition des tâches individuelles

Les tâches suivantes ont été distribuées entre les quatre membres de l'équipe :

| Guillaume | Kévin | Thomas | Quentin |
|-----------|-------|--------|---------|
| • Affichage de l'AST en graphviz<br>• GP: Compte rendu réussi<br>• Ajout de fonctions de test | • Première affichage de l'AST en cmd pour tester et debugger<br>• Mise à jour de l'affichage avec graphviz pour afficher les champs quand nécessaire | • Lexer : Implémentation du lexer puis le relier avec le  parseur de Bison<br>• Implémenter un wrapper pour encapsuler l'AST (C++) car la grammaire compile en C | • Gestion des erreurs sémantiques<br>• Debug de tout <br>|

## 4. Difficultés rencontrées

Au cours du développement, l'équipe a identifié deux difficultés principales :

**Grammaire difficile à débugger :** La complexité de la grammaire a rendu le processus de débogage particulièrement ardu, nécessitant une attention minutieuse et des outils de visualisation appropriés.

**Compatibilité entre code C++ et code C généré par Bison :** L'intégration entre le code C++ développé pour le projet et le code C généré automatiquement par Bison a posé des défis de compatibilité importants, notamment au niveau de l'encapsulation et de la gestion des interfaces.

## 5. Grammaire du langage

La grammaire (Bison) couvre les concepts suivants : classes (avec `extends`), constructeur, méthodes (typées et `void`), une classe `Main` avec la signature Java-like, instructions (déclarations/affectations, `if`/`else`, `for`, `return`, blocs), et des expressions avec appels de méthodes, accès/affectation de champs et opérateurs unaires/binaires avec précédences.

Extrait synthétique (EBNF simplifié) issu de `parser/grammar.y` :

```bnf
file            ::= class* class_Main

class           ::= 'class' IDENT '{' decl* '}'
									| 'class' IDENT 'extends' IDENT '{' decl* '}'

class_Main      ::= 'class' Main '{' 'public' 'static' 'void' main '(' 'String' IDENT '[' ']' ')' '{' stmt* '}' '}'

decl            ::= type IDENT ';'
									| constructor
									| method

constructor     ::= IDENT '(' params_opt ')' '{' stmt* '}'
method          ::= type IDENT '(' params_opt ')' '{' stmt* '}'
									| 'void' IDENT '(' params_opt ')' '{' stmt* '}'

params_opt      ::= ε | params
params          ::= type IDENT (',' type IDENT)*
type            ::= 'boolean' | 'int' | IDENT | 'String'

stmt            ::= ';'
									| expr ';'
									| type IDENT ';'
									| type IDENT '=' expr ';'
									| if_cond | for_loop
									| '{' stmt* '}'
									| 'return' ';' | 'return' expr ';'
									| method

if_cond         ::= 'if' '(' expr ')' stmt
									| 'if' '(' expr ')' stmt 'else' stmt

for_loop        ::= 'for' '(' expr_opt ';' expr_opt ';' expr_opt ')' stmt

expr            ::= INTEGER | STRING | 'true' | 'false' | 'this' | 'null'
									| '(' expr ')'
									| IDENT postfix
									| 'this' postfix
									| 'new' (IDENT|'String') '(' lexpr_opt ')'
									| '!' expr | '-' expr
									| '(' type ')' expr            /* cast */
									| expr '||' expr | expr '&&' expr
									| expr ('=='|'!=') expr
									| expr ('<'|'<='|'>'|'>=') expr | expr 'instanceof' type
									| expr ('+'|'-') expr | expr ('*'|'/'|'%') expr

postfix         ::= ε
									| '=' expr
									| '(' lexpr_opt ')'
									| '.' IDENT
									| '.' IDENT '=' expr
									| '.' IDENT '(' lexpr_opt ')'

lexpr_opt       ::= ε | lexpr
lexpr           ::= expr (',' expr)*
expr_opt        ::= ε | expr
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

| Étape | Membre(s) | Estimé (h) | Réel (h) | Commentaires |
|---|---|---:|---:|---|
| Conception de la grammaire (Bison) | Thomas + Quentin | 4 | 4 |  |
| Implémentation du lexer | Thomas | 4 | 5 |  |
| Construction de l'AST + wrappers | Thomas | 7 | 10 | Cette partie ne prend en compte que la durée d'implémentation de l'arbre, sa structure ayant déjà été définie au préalable |
| Gestion des erreurs sémantiques | Quentin | 5 | 7 | La documentation sur la gestion des erreurs manque cruellement de particité |
| Intégration parser ↔ AST + erreurs | Quentin + Thomas | 10 | 15 | |
| Visualisation Graphviz (DOT/PNG) |  Guillaume| 5 | 4 |  |
| Jeux d'essais (Ok/Erreurs) | Thomas, Guillaume, Kevin| 4 | 6 |  |

## 9. Conclusion

Le projet avance de manière structurée grâce à une répartition efficace des tâches et une collaboration étroite entre les membres de l'équipe. Les difficultés identifiées font l'objet d'un travail continu pour les résoudre et permettre la poursuite du développement du compilateur dans les meilleures conditions. Les éléments techniques requis (grammaire, structure AST, jeux d'essais) sont intégrés dans ce rapport.