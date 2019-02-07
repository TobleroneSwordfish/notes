import Prelude hiding (Num)
import qualified Prelude (Num)

type Num = Integer
type Var = String

type Z = Integer
type T = Bool

type State = Var -> Z

data Aexp = N Num | V Var | Mult Aexp Aexp |
    Add Aexp Aexp | Sub Aexp Aexp
    deriving (Show, Eq, Read)

data Bexp = TRUE | FALSE | Neg Bexp | And Bexp Bexp |
    Eq Aexp Aexp | Le Aexp Aexp
    deriving (Show, Eq, Read)

n_val :: Num -> Z
n_val n = n

s :: State
s "x" = 1
s "y" = 2
s "z" = 3
s _ = 0

a :: Aexp
a = Mult a1 a2 where
    a1 = Add (V "x") (V "y")
    a2 = Sub (V "z") (N 1)

a_val :: Aexp -> State -> Z
a_val (N n) st = n
a_val (V x) st = st x
a_val (Mult a1 a2) st = (a_val a1 st) * (a_val a2 st)
a_val (Add a1 a2) st = (a_val a1 st) + (a_val a2 st)
a_val (Sub a1 a2) st = (a_val a1 st) - (a_val a2 st)

b :: Bexp
b = Neg (Eq (Add (V "x") (V "y")) (N 4))

b_val :: Bexp -> State -> T
b_val TRUE st = True
b_val FALSE st = False
b_val (Neg b) st = not (b_val b st)
b_val (And b1 b2) st = (b_val b1 st) && (b_val b2 st)
b_val (Eq a1 a2) st = (a_val a1 st) == (a_val a2 st)
b_val (Le a1 a2) st = (a_val a1 st) <= (a_val a2 st)