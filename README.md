# Simple expression parser using recursive descent

### Current grammar

    Expr := Sum
    Sum := Prod + Sum | Prod - Sum | Prod
    Prod := "(" Sum ")" | "(" Sum ")" * Sum | "(" Sum ")" / Sum | num * Sum | num / Sum | num
    num := 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 { num }

WRONG GRAMMAR, TO DO a rewrite