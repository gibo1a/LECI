import java.util.Iterator;

@SuppressWarnings("CheckReturnValue")
public class Execute extends HelloBaseVisitor<String> {

   @Override public String visitMain(HelloParser.MainContext ctx) {
      String res = null;
      return visitChildren(ctx);
      //return res;
   }

   @Override public String visitGreetings(HelloParser.GreetingsContext ctx) {
      String name = visit(ctx.name());
      System.out.println("Olá " + name);
      return name;
      //return res;
   }

   @Override public String visitBye(HelloParser.ByeContext ctx) {
      String name = visit(ctx.name());
      System.out.println("Adeus " + name);
      return name;
      //return res;
   }

   @Override public String visitName(HelloParser.NameContext ctx) {
      String res = "";
      Iterator<HelloParser.WordContext> iterator = ctx.word().iterator();

      while(iterator.hasNext()){
         res+=(res.isEmpty() ? "" : " ") + visit(iterator.next());
      }
      return res;
      //return res;
   }

   @Override public String visitWord(HelloParser.WordContext ctx) {
      return ctx.ID().getText();
      //return res;
   }
}
