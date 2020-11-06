# Simple expression parser using recursive descent

### Current grammar

    Expr := Sum
    Sum := Prod + Sum | Prod - Sum | Prod
    Prod := "(" Sum ")" | "(" Sum ")" * Prod | "(" Sum ")" / Prod | num * Prod | num / Prod | num
    num := 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 { num }
