#ifndef AST_HPP
#define AST_HPP

#include "llvm/Support/Casting.h"
#include <memory>
#include <string>
#include <vector>

enum class AstKind {
  Variable,
  Integer,
  BinExpr,
  CallExpr,
  VariableDecl,
  JumpStmt,
  CompStmt,
};

class Ast;

using AstRef = Ast *;

class Ast {
  public:
  Ast(AstKind k) : kind(k) {
  }
  virtual ~Ast() = 0;
  virtual AstRef clone() const = 0;
  AstKind
  get_kind() const {
    return kind;
  }

  protected:
  Ast(const Ast &) = default;

  private:
  const AstKind kind;
};

class VariableAst : public Ast {
  public:
  VariableAst(const std::string &n) : Ast(AstKind::Variable), name(n) {
  }
  ~VariableAst() override = default;
  AstRef
  clone() const override {
    VariableAst *copy = new VariableAst(*this);
    return static_cast<AstRef>(copy);
  }
  static bool
  classof(const Ast *T) {
    return T->get_kind() == AstKind::Variable;
  }

  protected:
  VariableAst(const VariableAst &) = default;

  private:
  std::string name;
};

class IntegerAst : public Ast {
  public:
  IntegerAst(int v) : Ast(AstKind::Integer), value(v) {
  }
  ~IntegerAst() override = default;
  AstRef
  clone() const override {
    IntegerAst *copy = new IntegerAst(*this);
    return static_cast<AstRef>(copy);
  }
  static bool
  classof(const Ast *T) {
    return T->get_kind() == AstKind::Integer;
  }

  protected:
  IntegerAst(const IntegerAst &) = default;

  private:
  int value;
};

class BinExprAst : public Ast {
  public:
  BinExprAst(const AstRef &l, const AstRef &r)
      : Ast(AstKind::BinExpr), lhs(l), rhs(r) {
  }
  ~BinExprAst() override = default;
  AstRef
  clone() const override {
    AstRef l(lhs->clone()), r(rhs->clone());
    BinExprAst *copy = new BinExprAst(l, r);
    return static_cast<AstRef>(copy);
  }
  static bool
  classof(const Ast *T) {
    return T->get_kind() == AstKind::BinExpr;
  }

  private:
  AstRef lhs;
  AstRef rhs;
};

class CallExprAst : public Ast {
  public:
  using ArgList = std::vector<AstRef>;
  CallExprAst(const AstRef &c, const ArgList &a)
      : Ast(AstKind::CallExpr), callee(c), args(a) {
  }
  ~CallExprAst() override = default;
  AstRef
  clone() const override {
    AstRef c(callee->clone());
    ArgList as;
    for (auto &arg : args) {
      as.push_back(arg->clone());
    }
    CallExprAst *copy = new CallExprAst(c, as);
    return static_cast<AstRef>(copy);
  }
  static bool
  classof(const Ast *T) {
    return T->get_kind() == AstKind::CallExpr;
  }

  private:
  AstRef callee;
  ArgList args;
};

enum class DeclType {
  Param,
  Local,
};

class VariableDeclAst : public Ast {
  public:
  VariableDeclAst(const std::string &n, DeclType t)
      : Ast(AstKind::VariableDecl), name(n), type(t) {
  }
  ~VariableDeclAst() override = default;
  AstRef
  clone() const override {
    VariableDeclAst *copy = new VariableDeclAst(*this);
    return static_cast<AstRef>(copy);
  }
  static bool
  classof(const Ast *T) {
    return T->get_kind() == AstKind::VariableDecl;
  }

  protected:
  VariableDeclAst(const VariableDeclAst &) = default;

  private:
  std::string name;
  DeclType type;
};

class JumpStmtAst : public Ast {
  public:
  JumpStmtAst(const AstRef &e) : Ast(AstKind::JumpStmt), expr(e) {
  }
  ~JumpStmtAst() override = default;
  AstRef
  clone() const override {
    JumpStmtAst *copy = new JumpStmtAst(expr->clone());
    return static_cast<AstRef>(copy);
  }
  static bool
  classof(const Ast *T) {
    return T->get_kind() == AstKind::JumpStmt;
  }

  protected:
  JumpStmtAst(const JumpStmtAst &) = default;

  private:
  AstRef expr;
};

class CompStmtAst : public Ast {
  public:
  using DeclRef = VariableDeclAst *;
  CompStmtAst(const std::vector<DeclRef> &ds,
              const std::vector<AstRef> &ss)
      : Ast(AstKind::CompStmt), decls(ds), stmts(ss) {
  }
  ~CompStmtAst() override = default;
  AstRef
  clone() const override {
    std::vector<DeclRef> ds;
    for (auto &&d : decls) {
      ds.push_back(llvm::dyn_cast<VariableDeclAst>(d->clone()));
    }
    std::vector<AstRef> ss;
    for (auto &&s : stmts) {
      ss.push_back(s->clone());
    }
    CompStmtAst *copy = new CompStmtAst(ds, ss);
    return static_cast<AstRef>(copy);
  }

  private:
  std::vector<DeclRef> decls;
  std::vector<AstRef> stmts;
};

#endif /* !AST_HPP */
