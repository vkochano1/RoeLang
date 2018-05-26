namespace roe
{
  class RuntimeException : public ExceptionBase
  {
  public:
    RuntimeException()
      : ExceptionBase("Runtime exception:")
    {
    }
  };
}
