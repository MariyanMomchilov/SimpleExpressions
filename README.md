# Simple expression parser using recursive descent

### Current grammar

    Expr := Prod { Sum }
    Sum := + Prod | - Prod
    Prod := Operand { ProOp }
    ProOp := * Prod | / Prod 
    Operand := num | "(" Expr ")"
    num := 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 { num }

    
    | - or
    { S } - 0 or more times S 

