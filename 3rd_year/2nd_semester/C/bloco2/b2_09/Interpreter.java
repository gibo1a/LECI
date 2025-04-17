import java.util.HashMap;

@SuppressWarnings("CheckReturnValue")
public class Interpreter extends FractionBaseVisitor<Fraction> {

   protected HashMap<String,Fraction> variables = new HashMap<>();

   @Override public Fraction visitAssignmentStat(FractionParser.AssignmentStatContext ctx) {
      Fraction res = null;
      return visitChildren(ctx);
      //return res;
   }

   @Override public Fraction visitPrintStat(FractionParser.PrintStatContext ctx) {
      Fraction res = visit(ctx.print());
      if(res != null){
         System.out.println(res);
      }
      return res;
   }

    @Override public Fraction visitPrint(FractionParser.PrintContext ctx) {
      return visit(ctx.expr());
   }

    @Override public Fraction visitAssignment(FractionParser.AssignmentContext ctx) {
       String var = ctx.ID().getText();
      Fraction frac = visit(ctx.expr());
      variables.put(var, frac);
      return frac;
   }

   @Override public Fraction visitExprFrac(FractionParser.ExprFracContext ctx) {
      Fraction res = null;
      Fraction f1 = visit(ctx.num(0));
      Fraction f2 = visit(ctx.num(1));
      res = new Fraction(f1.getNum(), f2.getNum());
      return res;
   }

    @Override public Fraction visitExprAddSub(FractionParser.ExprAddSubContext ctx) {
      Fraction res = null;
      Fraction f1 = visit(ctx.expr(0));
      Fraction f2 = visit(ctx.expr(1));
      String op = ctx.op.getText();
   
      if(f1 != null && f2 != null){
         switch(op){
            case "+":
               res = Fraction.addFrac(f1,f2);
               break;
            
            case "-":
               res = Fraction.subFrac(f1,f2);
               break;

            default:
               break;
         }
      }
      return res;
   }

   @Override public Fraction visitExprPot(FractionParser.ExprPotContext ctx) {
      Fraction res = null;
      Fraction e1 = visit(ctx.expr(0));
      Fraction e2 = visit(ctx.expr(1));
      double d1 = (double) e1.getNum();
      double d2 = (double) e2.getNum();
      double d3 = (double) e1.getDen();
      int new_num = (int) Math.pow(d1, d2);
      int new_den = (int) Math.pow(d3,d2);
      res = new Fraction(new_num, new_den);
      return res;
   }

   @Override public Fraction visitExprParent(FractionParser.ExprParentContext ctx) {
      return visit(ctx.expr());
   }

   @Override public Fraction visitExprInt(FractionParser.ExprIntContext ctx) {
      return visit(ctx.num());
   }

   @Override public Fraction visitExprDivMul(FractionParser.ExprDivMulContext ctx) {
      Fraction res = null;
        Fraction f1 = visit(ctx.expr(0));
        Fraction f2 = visit(ctx.expr(1));
        String op = ctx.op.getText();

        if(f1 != null && f2 != null){
            switch(op){
                case "*":
                res = Fraction.multFrac(f1, f2);
                case ":":
                res = Fraction.divFrac(f1, f2);
                break;
                default:
                break;
            }
        }
        return res;
   }

   @Override public Fraction visitExprID(FractionParser.ExprIDContext ctx) {
       String id = ctx.ID().getText();

      if(variables.containsKey(id)){
         return variables.get(id);
      }else{
         System.err.println("Variable not found");
         return null;
      }
   }

   @Override public Fraction visitReduceExpr(FractionParser.ReduceExprContext ctx) {
      Fraction res = visit(ctx.expr());
      int mdc = Fraction.gcd(res.getNum(),res.getDen());
      return new Fraction(res.getNum()/mdc, res.getDen()/mdc);
   }

   @Override public Fraction visitExprUnary(FractionParser.ExprUnaryContext ctx) {
      Fraction res = null;
      Integer num = Integer.parseInt(ctx.INTEGER().getText()); 
      String op = "+";
      if(ctx.op != null){
         op = ctx.op.getText();
      }

      switch (op) {
         case "-":
            num = (-1) * num;
            res = new Fraction(num);
            break;
         default:
            res = new Fraction(num);
            break;
      }
      return res;
   }
}
