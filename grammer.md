$$
\begin{align}
    [\text{main}] &\to [\text {program}] \\
    [\text{program}] &\to [\text {Statement*}] \\
    [\text{Statement}] &\to
    \begin{cases} 
        Expression \\
        If \\
        For \\
        While \\
        When \\
        delete \\
        using \\
        Assign \\
    \end{cases} \\
    [\text{Operator}] &\to [\text{+ - = /}]\\
    [\text{Expression}] &\to [\text{Operand operator Operand}] \\
    [\text{Assign}] &\to
    \begin{cases}
        \text{Type Identifier = Expr} \\
        \text{Identifier operator Expr} \\
    \end{cases} \\
\end{align}
$$