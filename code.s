# 1. CONSIDERAR UM PROCESSADOR SEM FORWARDING 
# (5-stage processor w/o forwarding or hazard detection)
#    1A. Identificar os hazards [2 pontos]
#    1B. Resolver com NOPs [1 ponto]
#    1C. Reordenar as instrucoes de forma a reduzir o numero de NOPs [1 ponto]
# 
# 2. CONSIDERAR UM PROCESSADOR COM FORWARDING
#    Comparar a estat?stica (IPC, racio instrucoes uteis/total) de 1B, 1C no
#    processador original (5-stage processor w/o forwarding or hazard detection)
#    e completo (5-stage processor) [1 ponto]

# Computer Architectures
# Lab: Pipelining

# The following program processes two arbitrarily sized one-dimensional
# vectors composed by N integer elements, in order to execute
# the following pseudo-code algorithm:

#    int a[N] = { ..... }
#    int b[N] = { ..... }
#    int N = /* Vectors Size */
#    int res = 0;
#    int ran = 1;
#    register int k = N-1;
#    while (b[k] >= a[k]) {
#        res += (b[k] - a[k])*b[k];
#        ran *= a[k]/b[k];
#        k--;
#    }


# Data section
# IMPORTANT: do not change this section
.data
a:    .word   3, 5, -6, 6, -7, 7, 10, 1, 2, 2, -2, -1
b:    .word   15, -13, 12, -11, 11, 8, 4, 8, 8, 5, 2, 2
ran:  .word   1 
res:  .zero   4
N:    .word   12

# Program section
# NOTE: Upon start, the Global-Pointer (gp=x3) points to the beginning of .data section
.text
    # x3 = a's left index
    addi x13, x3, 48    # x13 = b's left index
    addi x12, x13, -4   # x12 = &(a[N-1]) = a's right index
    addi x14, x13, 44   # x14 = &(b[N-1]) = b's right index
    addi x16, x14, 4    # x16 = &ran 
    addi x17, x14, 8    # x17 = &res    
    li x15, 0           # x15 = res
    lw x8, 0(x16)       # x8 = ran
    
while:
    lw x18,0(x12)       # x18 = a[k]
    lw x19,0(x14)       # x19 = b[k]
    bgt x18, x19, end   # a[k] > b[k] -> while end
    
    sub x5, x19, x18    # (b[k] - a[k]);
    mul x5, x5, x19     # (b[k] - a[k])*b[k]
    add x15, x15, x5    # res += (b[k] - a[k])*b[k]
    
    div x6, x19, x18    # b[k]/a[k]
    mul x8, x8, x6      # ran *= b[k]/a[k]
    
    # k--
    addi x12, x12, -4
    addi x14, x14, -4

    jal x0, while
    
end:

    sw x8, 0(x16)    # ran = 128
    sw x15, 0(x17)   # res = 1935360