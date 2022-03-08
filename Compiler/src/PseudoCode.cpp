#include "Luau/PseudoCode.h"
#include <sstream>
namespace Luau
{
    class PseudoCode : public AstVisitor
    {
        std::ostringstream buf;

        virtual bool visit(class AstNode* node)
        {
            buf << "NODE:" << node->classIndex << "\n";
            return true;
        }

        virtual bool visit(class AstExpr* node)
        {
            buf << "EXPR:" << node->classIndex << "\n";
            return true;
        }

        virtual bool visit(class AstExprGroup* node)
        {
            buf << "EGRP\n";
            return true;
        }
        virtual bool visit(class AstExprConstantNil* node)
        {
            buf << "CSTV\n";
            return true;
        }
        virtual bool visit(class AstExprConstantBool* node)
        {
            buf << "CSTB:"<<(node->value?"true":"false") <<"\n";
            return true;
        }
        virtual bool visit(class AstExprConstantNumber* node)
        {
            buf << "CSTN:"<<(node->value) <<"\n";
            return true;
        }
        virtual bool visit(class AstExprConstantString* node)
        {
            buf << "CSTS:"<<(node->value.data) <<"\n";
            return true;
        }
        virtual bool visit(class AstExprLocal* node)
        {
            buf << "VLOC:" << node->local->name.value << "\n";
            return true;
        }
        virtual bool visit(class AstExprGlobal* node)
        {
            buf << "VGLB:" << node->name.value << "\n";
            return true;
        }
        virtual bool visit(class AstExprVarargs* node)
        {
            return visit((class AstExpr*)node);
        }
        virtual bool visit(class AstExprCall* node)
        {
            buf << "ECAL:" << node->args.size << "\n"; // Follow: Function, Args x n
            return true;
        }
        virtual bool visit(class AstExprIndexName* node)
        {
            buf << "ETIN:" << node->index.value << "\n"; // Follow: Indexed Expr
            return true;
        }
        virtual bool visit(class AstExprIndexExpr* node)
        {
            buf << "ETIE\n"; // Follow: Indexed Expr, Index Expr
            return true;
        }
        virtual bool visit(class AstExprFunction* node)
        {
            buf << "EFCT:" << node->args.size << "\n"; // Follow: Arg Names x n, Body
            for (AstLocal* arg : node->args)
                buf << "SLNM:" << arg->name.value << ":" << (arg->annotation?"T":"_") << "\n";

            return true;
        }
        virtual bool visit(class AstExprTable* node)
        {
            buf << "ETBL:" << node->items.size << "\n"; // Follow: Items x n
            return true;
        }
        virtual bool visit(class AstExprUnary* node)
        {
            buf << "EUNA:" << toString(node->op) << "\n"; // Follow: Sub Expr
            return true;
        }
        virtual bool visit(class AstExprBinary* node)
        {
            buf << "EBIN:" << toString(node->op) << "\n"; // Follow: Left and Right
            return true;
        }
        virtual bool visit(class AstExprTypeAssertion* node)
        {
            return visit((class AstExpr*)node);
        }
        virtual bool visit(class AstExprIfElse* node)
        {
            buf << "EIFE\n"; //Follow: Cond, IfTrue, IfFalse
            return true;
        }
        virtual bool visit(class AstExprError* node)
        {
            return visit((class AstExpr*)node);
        }

        virtual bool visit(class AstStat* node)
        {
            buf << "STAT:" << node->classIndex << "\n";
            return true;
        }

        virtual bool visit(class AstStatBlock* node)
        {
            buf << "SBLK:" << node->body.size << "\n";
            return true;
        }
        virtual bool visit(class AstStatIf* node)
        {
            buf << "SIF_:" << (node->elseLocation&&true) << "\n"; //Follow: Cond, Then, (Else)
            return true;
        }
        virtual bool visit(class AstStatWhile* node)
        {
            buf << "SWHL\n"; //Follow: Condition, Body
            return true;
        }
        virtual bool visit(class AstStatRepeat* node)
        {
            buf << "SRPT\n"; //Follow: Body, Condition
            return true;
        }
        virtual bool visit(class AstStatBreak* node)
        {
            buf << "SBRK\n";
            return true;
        }
        virtual bool visit(class AstStatContinue* node)
        {
            buf << "SCNT\n";
            return true;
        }
        virtual bool visit(class AstStatReturn* node)
        {
            buf << "SRTN:" << node->list.size << "\n";
            return true;
        }
        virtual bool visit(class AstStatExpr* node)
        {
            buf << "SEXP\n";
            return true;
        }
        virtual bool visit(class AstStatLocal* node)
        {
            buf << "SLCL:" << node->values.size << "\n";
            for (AstLocal* var : node->vars)
            {
                buf << "SLNM:" << var->name.value << ":" << (var->annotation?"T":"_") << "\n";
            }
            return true;
        }
        virtual bool visit(class AstStatFor* node)
        {
            buf << "SFOR:" << node->var->name.value << ":" << ((node->step)?1:0) << "\n"; //Follow First,Last,(Step)
            return true;
        }
        virtual bool visit(class AstStatForIn* node)
        {
            buf << "SFRT\n";
            return true;
        }
        virtual bool visit(class AstStatAssign* node)
        {
            buf << "SAGN:" << node->values.size << "\n"; //Follow: Var x n, Value x n
            return true;
        }
        virtual bool visit(class AstStatCompoundAssign* node)
        {
            buf << "SCAG:" << toString(node->op) << "\n"; //Follow Var, Value
            return true;
        }
        virtual bool visit(class AstStatFunction* node)
        {
            buf << "SFCT\n"; //Follow: Name, Func
            return true;
        }
        virtual bool visit(class AstStatLocalFunction* node)
        {
            buf << "SLFN:" << node->name->name.value <<"\n"; //Follow: Func
            return true;
        }
        virtual bool visit(class AstStatTypeAlias* node)
        {
            return visit((class AstStat*)node);
        }
        virtual bool visit(class AstStatDeclareFunction* node)
        {
            return visit((class AstStat*)node);
        }
        virtual bool visit(class AstStatDeclareGlobal* node)
        {
            return visit((class AstStat*)node);
        }
        virtual bool visit(class AstStatDeclareClass* node)
        {
            return visit((class AstStat*)node);
        }
        virtual bool visit(class AstStatError* node)
        {
            return visit((class AstStat*)node);
        }

        // By default visiting type annotations is disabled; override this in your visitor if you need to!
        virtual bool visit(class AstType* node)
        {
            buf << "TYPE:" << node->classIndex << "\n";
            return true;
        }

        virtual bool visit(class AstTypeReference* node)
        {
            buf << "TREF:" << node->name.value << ":" << node->parameters.size << "\n";
            return true;
        }
        virtual bool visit(class AstTypeTable* node)
        {
            return visit((class AstType*)node);
        }
        virtual bool visit(class AstTypeFunction* node)
        {
            return visit((class AstType*)node);
        }
        virtual bool visit(class AstTypeTypeof* node)
        {
            return visit((class AstType*)node);
        }
        virtual bool visit(class AstTypeUnion* node)
        {
            return visit((class AstType*)node);
        }
        virtual bool visit(class AstTypeIntersection* node)
        {
            return visit((class AstType*)node);
        }
        virtual bool visit(class AstTypeSingletonBool* node)
        {
            return visit((class AstType*)node);
        }
        virtual bool visit(class AstTypeSingletonString* node)
        {
            return visit((class AstType*)node);
        }
        virtual bool visit(class AstTypeError* node)
        {
            return visit((class AstType*)node);
        }

        virtual bool visit(class AstTypePack* node)
        {
            return false;
        }
        virtual bool visit(class AstTypePackExplicit* node)
        {
            return visit((class AstTypePack*)node);
        }
        virtual bool visit(class AstTypePackVariadic* node)
        {
            return visit((class AstTypePack*)node);
        }
        virtual bool visit(class AstTypePackGeneric* node)
        {
            return visit((class AstTypePack*)node);
        }

    public:
        std::string getPseudoCode() { return buf.str(); }
    };

    std::string generatePseudoCode(AstExprFunction *func)
    {
        PseudoCode generator;
        func->visit(&generator);
        return generator.getPseudoCode();
    }
}
